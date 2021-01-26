/* Copyright 1990-2005, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Xenos: file directory, attributes, & permission                         */


#include <sys/types.h>
#include <unistd.h>

#include "j.h"
#include "x.h"

char* toascbuf(char* s){ return s;}
char* tounibuf(char* s){ return s;}

#if (SYS & SYS_DOS)

#include <ctype.h>
#include <io.h>
#include <dos.h>
#include <direct.h>
#include <time.h>

#ifndef F_OK            /* for access() */
#define F_OK            0x00
#define X_OK            0x01
#define W_OK            0x02
#define R_OK            0x04
#endif

#ifndef _A_VOLID
#define _A_VOLID        0x00
#endif

#define _A_ALL          (_A_NORMAL+_A_RDONLY+_A_HIDDEN+_A_SYSTEM+_A_VOLID+ \
                         _A_SUBDIR+_A_ARCH)

static A jtattv(J jt,U x){A z;C*s;
 GAT0(z,LIT,6,1); s=CAV(z);
 s[0]=x&_A_RDONLY?'r':'-';
 s[1]=x&_A_HIDDEN?'h':'-';
 s[2]=x&_A_SYSTEM?'s':'-';
 s[3]=x&_A_VOLID ?'v':'-';
 s[4]=x&_A_SUBDIR?'d':'-';
 s[5]=x&_A_ARCH  ?'a':'-';
 return z;
}    /* convert from 16-bit attributes x into 6-element string */

static S jtattu(J jt,A w){C*s;I i,n;S z=0;
 RZ(w=vslit(w)); 
 n=AN(w); s=CAV(w);
 for(i=0;i<n;++i)switch(s[i]){
  case 'r': z^=_A_RDONLY; break;
  case 'h': z^=_A_HIDDEN; break;
  case 's': z^=_A_SYSTEM; break;
  case 'v': z^=_A_VOLID;  break;
  case 'd': z^=_A_SUBDIR; break;
  case 'a': z^=_A_ARCH;   break;
  case '-':               break;
  default:  ASSERT(0,EVDOMAIN);
 }
 return z;
}    /* convert from 6-element string into 16-bit attributes */

F1(jtfullname){C dirpath[_MAX_PATH];
 RZ(w=str0(vslit(w)));
 wchar_t wdirpath[_MAX_PATH];
 RZ(w=toutf16x(w)); USAV(w)[AN(w)]=0;
 _wfullpath(wdirpath,USAV(w),_MAX_PATH);
 WideCharToMultiByte(CP_UTF8,0,wdirpath,1+(int)wcslen(wdirpath),dirpath,_MAX_PATH,0,0);
 return cstr(dirpath);
}


F1(jtjfperm1){A y,fn,z;C *s;F f;int x; US *p,*q;
 F1RANK(0,jtjfperm1,UNUSED_VALUE);
 RE(f=stdf(w)); if(f){RZ(y=fname(sc((I)f)))} else ASSERT(y=AAV(w)[0],EVFNUM)
 RZ(fn=toutf16x(y)); USAV(fn)[AN(fn)]=0;  // install termination
 p=USAV(fn); q=p+AN(fn)-3;
 GAT0(z,LIT,3,1); s=CAV(z);
 x=_waccess(p,R_OK); if(0>x)return jerrno();
 s[0]=x?'-':'r';
 s[1]=_waccess(p,W_OK)?'-':'w';
 s[2]=wcscmp(q,L"exe")&&wcscmp(q,L"bat")&&wcscmp(q,L"com")?'-':'x';
 return z;
}

F2(jtjfperm2){A y,fn;C*s;F f;int x=0;US *p;
 F2RANK(1,0,jtjfperm2,UNUSED_VALUE);
 RE(f=stdf(w)); if(f){RZ(y=fname(sc((I)f)))} else ASSERT(y=AAV(w)[0],EVFNUM)
 RZ(a=vslit(a)); ASSERT(3==AN(a),EVLENGTH); 
 RZ(fn=toutf16x(y)); USAV(fn)[AN(fn)]=0;  // install termination
 s=CAV(y);
 p=USAV(fn);;
 s=CAV(a);
 if('r'==s[0]) x|=S_IREAD;  else ASSERT('-'==s[0],EVDOMAIN);
 if('w'==s[1]) x|=S_IWRITE; else ASSERT('-'==s[1],EVDOMAIN);
 if('x'==s[2]) x|=S_IEXEC;  else ASSERT('-'==s[2],EVDOMAIN);
 return _wchmod(p,x)?jerrno():mtm;
}

#endif

/* jdir produces a 5-column matrix of boxes:                 */
/* 0 name                                                    */
/* 1 time of last write, y m d h m s                         */
/* 2 size                                                    */
/* 3 permission -- 0 read  1 write  2 execute                */
/* 4 attributes                                              */
/*   0 read-only    3 volume label                           */
/*   1 hidden       4 directory                              */
/*   2 system       5 archive (modified since last back-up)  */


#if (SYS & SYS_UNIX)

/* FIXME:   rename J link() function so we can include unistd.h */
// undefs to avoid darwin warnings - should be a better fix
#undef R_OK
#undef W_OK
#undef X_OK
#define R_OK    4               /* Test for read permission.    */
#define W_OK    2               /* Test for write permission.   */
#define X_OK    1               /* Test for execute permission. */

#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#if SYS&(SYS_SUN4+SYS_SGI)
#include "fnmatch.h"
#else
#include <fnmatch.h>
#endif


/* Return mode_t formatted into 11-character buffer supplied by the caller.  The last byte of the buffer is the string terminator \0 */
static C*modebuf(mode_t m,C* b){C c;I t=m;
 strcpy(b+1,"rwxrwxrwx");
 DO(9, if(!(m&1))b[9-i]='-'; m>>=1;); 
 if(t&S_ISUID)b[3]=(b[3]=='x')?'s':'S';
 if(t&S_ISGID)b[6]=(b[6]=='x')?'s':'S';
 if(t&S_ISVTX)b[9]=(b[9]=='x')?'t':'T';
 switch(t&S_IFMT){
  case S_IFBLK:  b[0]='b'; break;
  case S_IFCHR:  b[0]='c'; break;
  case S_IFDIR:  b[0]='d'; break;
#if !(SYS & SYS_UNIX)
  case S_IFFIFO: b[0]='f'; break;    /*IVL */
#endif
  case S_IFLNK:  b[0]='l'; break;
  case S_IFSOCK: b[0]='s'; break;
  case S_IFREG:  b[0]='-'; break;
  default:       b[0]='?';
 }
 return b;
}


static int ismatch(J jt,C*pat,C*name,struct stat *dirstatbuf,C *diratts, C *dirmode,C *dirrwx,C *dirnamebuf,C *dirbase){ 

 strcpy(dirbase,name); if(stat(dirnamebuf,dirstatbuf))return 0;
 if('.'!=*pat && ((!strcmp(name,"."))||(!strcmp(name,".."))))return 0;
 if(fnmatch(pat,name,0)) return 0;
/* Set up dirrwx, diratts, and dirmode for this file */
 dirrwx[0]=access(dirnamebuf,R_OK)?'-':'r';
 dirrwx[1]=access(dirnamebuf,W_OK)?'-':'w';
 dirrwx[2]=access(dirnamebuf,X_OK)?'-':'x';
 strcpy(diratts,"------");
 diratts[0]=(dirrwx[0]=='r'&&dirrwx[1]=='-')?'r':'-';
 diratts[1]=('.'==name[0])?'h':'-';
 modebuf(dirstatbuf[0].st_mode,dirmode);
 diratts[4]=('d'==dirmode[0])?'d':'-';
 return 1;
}

static A jtdir1(J jt,struct dirent*f,struct stat *dirstatbuf,C *diratts, C *dirmode,C *dirrwx){A z,*zv;C*s,att[16];I n,ts[6],i,m,sz;S x;struct tm tmr,*tm=&tmr;
 tm=localtime_r(&dirstatbuf[0].st_mtime,tm);
 ts[0]=1900+tm->tm_year; ts[1]=1+tm->tm_mon; ts[2]=tm->tm_mday;
 ts[3]=tm->tm_hour; ts[4]=tm->tm_min; ts[5]=tm->tm_sec;
 s=f->d_name; n=strlen(s);
 GAT0(z,BOX,6,1); zv=AAV(z);
 RZ(zv[0]=vec(LIT,n,s)); 
 RZ(zv[1]=vec(INT,6L,ts));
 sz=dirstatbuf[0].st_size;
 sz=sz<0?-1:sz;
 RZ(zv[2]=sc(sz));
 RZ(zv[3]=vec(LIT,3L, dirrwx ));
 RZ(zv[4]=vec(LIT, 6L,diratts));
 RZ(zv[5]=vec(LIT,10L,dirmode));
 return z;
}

F1(jtjdir){PROLOG(0103);A*v,z,*zv;C*dir,*pat,*s,*x;I j=0,n=32;DIR*DP;struct dirent *f;
 C diratts[7]; C dirmode[11];  C dirrwx[3];
 struct stat dirstatbuf[3];  // for some reason there were 2 dummy blocks reserved after the buffer for 32-bit Linux.  Preserve that
 C dirnamebuf[NPATH];  // workarea
 ARGCHK1(w);
 RZ(w=str0(vslit(!AR(w)&&BOX&AT(w)?ope(w):w)));
 s=CAV(w);
 if(x=strrchr(s,'/')){dir=s==x?(C*)"/":s; pat=x+1; *x=0;}else{dir="."; pat=s;}
 if(NULL==(DP=opendir(dir)))return reshape(v2(0L,6L),ds(CACE));
 /*
  * SYSV and BSD have different return types for sprintf(),
  * so we use less efficient but portable code.
  */
 sprintf(dirnamebuf,"%s/",dir); C * dirbase=dirnamebuf+strlen(dirnamebuf); f=readdir(DP);
 GATV0(z,BOX,n,1); zv=AAV(z);
 while(f){
  if(ismatch(jt,pat,f->d_name,dirstatbuf,diratts,dirmode,dirrwx,dirnamebuf,dirbase)){
   if(j==n){RZ(z=ext(0,z)); n=AN(z); zv=AAV(z);}
   RZ(zv[j++]=jtdir1(jt,f,dirstatbuf,diratts,dirmode,dirrwx));
  }
  f=readdir(DP);
 }
 closedir(DP);
 z=j?ope(j<n?vec(BOX,j,zv):z):reshape(v2(0L,6L),ds(CACE));
 EPILOG(z);
}



F1(jtjfatt1){ASSERT(0,EVNONCE);}
F2(jtjfatt2){ASSERT(0,EVNONCE);}


F1(jtjfperm1){A y;F f;C b[11];
 struct stat dirstatbuf[3];
 F1RANK(0,jtjfperm1,UNUSED_VALUE);
 RE(f=stdf(w)); if(f){RZ(y=fname(sc((I)f)));y=str0(y);} else ASSERT(y=str0(vslit(AAV(w)[0])),EVFNUM)
 if(0!=stat(CAV(y),dirstatbuf))return jerrno();
 return vec(LIT,9L,1+modebuf(dirstatbuf[0].st_mode,b));
}


static const struct tperms {C*c;I p[4];} permtab[]=
    {  {"-r"  ,{0,S_IRUSR}},
       {"-w"  ,{0,S_IWUSR}},
       {"-xSs",{0,S_IXUSR,S_ISUID,S_ISUID+S_IXUSR}},
       {"-r"  ,{0,S_IRGRP}},
       {"-w"  ,{0,S_IWGRP}},
       {"-xSs",{0,S_IXGRP,S_ISGID,S_ISGID+S_IXGRP}},
       {"-r"  ,{0,S_IROTH}},
       {"-w"  ,{0,S_IWOTH}},
       {"-xTt",{0,S_IXOTH,S_ISVTX,S_ISVTX+S_IXOTH}},
    };

F2(jtjfperm2){A y;C*s;F f;int x=0,i;C*m;
 F2RANK(1,0,jtjfperm2,UNUSED_VALUE);
 RE(f=stdf(w)); if(f){RZ(y=fname(sc((I)f)));y=str0(y);} else ASSERT(y=str0(vslit(AAV(w)[0])),EVFNUM)
 RZ(a=vslit(a)); ASSERT(9==AN(a),EVLENGTH); s=CAV(a);
 for(i=0;i<9;i++)
    {ASSERT(NULL!=(m=strchr(permtab[i].c,s[i])),EVDOMAIN);
     x|=permtab[i].p[m-permtab[i].c];}
 return chmod(CAV(y),x)?jerrno():mtm;
}


#endif

/* ----------------------------------------------------------------------- */


#if ! (SYS & SYS_DOS)
F1(jtfullname){return w;}
#endif
