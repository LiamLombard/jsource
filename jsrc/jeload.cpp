/* Copyright 1990-2008, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
// utilities for JFE to load JE, initiallize, and run profile sentence
// JFEs are jconsole, jwdw, and jwdp
#include <string>
#include <stdexcept>

extern "C" {

#define PLEN 1000 // path length

 #include <unistd.h>
 #include <dlfcn.h>
 #define GETPROCADDRESS(h,p)	dlsym(h,p)
 #define _stdcall
 #define filesep '/'
 #define filesepx "/"
 #ifdef __MACH__
  extern int _NSGetExecutablePath(char*, int*);
  #define JDLLNAME "libj.dylib"
 #else
  #include <sys/utsname.h>
  #define JDLLNAME "libj.so"
 #endif

#include "j.h"
#include "jversion.h"
#include <cstdint>

static void* hjdll; // handle to J DLL
static J jt;
static JDoType jdo;
static JFreeType jfree;
static JgaType jga;
static JGetLocaleType jgetlocale;
static JGetAType jgeta;
static JSetAType jseta;
char path[PLEN];
char pathdll[PLEN];
static char jdllver[20];
static int FHS=0; // Not sure what this is


int jedo(char* sentence)
{
    return jdo(jt,(C*)sentence);
}

A jegeta(I n, char* s){return jgeta(jt,n,(C*)s);}
I jeseta(I n,char* name,I x,char* d){return jseta(jt,n,(C*)name,x,(C*)d);}

void jefree(){jfree(jt);}
char* jegetlocale(){return (char*)jgetlocale(jt);}
A jega(I t, I n, I r, I*s){return jga(jt,t,n,r,s);}

void* jehjdll() { return hjdll; }

auto je_load_procedure_addresses(void* hjdll, void* callbacks) -> void {
    auto jsm = reinterpret_cast<JSMType>(dlsym(hjdll,"JSM"));
    jsm(jt,callbacks);
    jdo        = (JDoType)        dlsym(hjdll,"JDo");
    jfree      = (JFreeType)      dlsym(hjdll,"JFree");
    jga        = (JgaType)        dlsym(hjdll,"Jga");
    jgetlocale = (JGetLocaleType) dlsym(hjdll,"JGetLocale");
    jgeta      = (JGetAType)      dlsym(hjdll,"JGetA");
    jseta      = (JSetAType)      dlsym(hjdll,"JSetA");
};

// load JE, Jinit, getprocaddresses, JSM
J jeload(void* callbacks) {
    hjdll = dlopen(pathdll,RTLD_LAZY);

    if(!hjdll) {
        char* error = dlerror();
        printf( "ERROR\tCould not open library globally: %s\n", error ? error : "" );
        return nullptr;
    }

    jt = static_cast<JST*>(reinterpret_cast<JInitType>(dlsym(hjdll,"JInit"))());
    if (!jt) return nullptr;
    je_load_procedure_addresses(hjdll, callbacks);
    return jt;
}

// set path and pathdll (wpath also set for win)
// WIN arg is 0, Unix arg is argv[0]
void jepath(char* arg,char* lib)
{

 struct stat st;

 int32_t const sz  = 4000;
 int32_t len = sz; // Cant be const for function call _NSGetExecutablePath

 char arg2[sz];
 char arg3[sz];
 char* src;
 char *snk;
 // try host dependent way to get path to executable
 // use arg if they fail (arg command in PATH won't work)
#ifdef __MACH__
 int n=_NSGetExecutablePath(arg2,&len);
 if(0!=n) strcat(arg2,arg);
#else
 int n=readlink("/proc/self/exe",arg2,sizeof(arg2));
 if(-1==n) strcpy(arg2,arg); else arg2[n]=0;
#endif
 // arg2 is path (abs or relative) to executable or soft link
 n=readlink(arg2,arg3,sz);
 if(-1==n) strcpy(arg3,arg2); else arg3[n]=0;
 if('/'==*arg3)
  strcpy(path,arg3);
 else
 {
  if(!getcwd(path,sizeof(path)))path[0]=0;
  strcat(path,"/");
  strcat(path,arg3);
 }
 *(1+strrchr(path,'/'))=0;
 // remove ./ and backoff ../
 snk=src=path;
 while(*src)
 {
	 if('/'==*src&&'.'==*(1+src)&&'.'==*(2+src)&&'/'==*(3+src))
	 {
		 *snk=0;
		 snk=strrchr(path,'/');
		 snk=nullptr==snk?path:snk;
		 src+=3;
	 }
	 else if('/'==*src&&'.'==*(1+src)&&'/'==*(2+src))
      src+=2;
	 else
	  *snk++=*src++;
 }
 *snk=0;
 snk=path+strlen(path)-1;
 if('/'==*snk) *snk=0;
 strcpy(pathdll,path);
 strcat(pathdll,filesepx);
 strcat(pathdll,JDLLNAME);

 if(*lib)
 {
	 if(filesep==*lib || ('\\'==filesep && ':'==lib[1]))
		 strcpy(pathdll,lib); // absolute path
	 else
	 {
		 strcpy(pathdll,path);
		 strcat(pathdll,filesepx);
		 strcat(pathdll,lib); // relative path
	 }
 }
}

// called by jwdp (java jnative.c) to set path
void jesetpath(char* arg)
{
	strcpy(pathdll,arg); // jwdp gives path to j.dll
	strcpy(path,arg);
	if(strrchr(path,filesep))*(strrchr(path,filesep)) = 0;
}


}

extern "C" void jefail()
{
    throw std::invalid_argument("Load library " + std::string(pathdll) + " failed: " + std::string(strerror(errno)));
}

// build and run first sentence to set BINPATH, ARGV, and run profile
// arg is command line ready to set in ARGV_z_
// type is 0 normal, 1 -jprofile xxx, 2 ijx basic, 3 nothing
// profile[ARGV_z_=:...[BINPATH=:....
// profile is from BINPATH, ARGV, ijx basic, or nothing
extern "C" int jefirst(int type, char* arg)
{

    int r;

    std::string input;

    // If normal
    if(type == 0) {
        if (!FHS)
            input.append("(3 : '0!:0 y')<BINPATH,'");
        else {
            input.append("(3 : '0!:0 y')<'/etc/j/");
            input.append(jdllver);
        }
        input.append(filesepx);
        input.append("profile.ijs'");
    }
    else if(type == 1)
        input.append("(3 : '0!:0 y')2{ARGV");
    else if(type == 2)
        input.append("");
    else
        input.append("i.0 0");

    input.append("[ARGV_z_=:");
    input.append(arg);





#if defined(__MACH__)
    input.append("[UNAME_z_=:'Darwin'");
#endif
    input.append("[BINPATH_z_=:'");

    // Getting bin path
    std::string p{path};
    for(const auto &i: p){
        if(i == '\'')
            input += '\'';
        input += i;
    }
    input.append("'[LIBFILE_z_=:'");
    p = std::string(pathdll);
    for(const auto &i: p){
        if(i == '\'')
            input += '\'';
        input += i;
    }
    input.append("'");

    // TODO: When jedo is refactored, change this
    auto in = new char[2000+strlen(arg)];
    strcpy(in,input.c_str());
    r=jedo(in);
    free(in);

    return r;
}