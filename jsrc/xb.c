/* Copyright 1990-2014, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Xenos: Binary Representation                                            */

#include "j.h"
#include "x.h"


F1(jtstype){RZ(w); R sc(AT(w)&-AT(w));}
     /* 3!:0 w */

// a is integer atom or list, values indicating the desired result
// atom values in x: 0=NJA, others reserved
F2(jtnouninfo2){A z;
 RZ(a&&w);
 RZ(a=vi(a)); // convert to integer, error if can't
 ASSERT(AR(a)<2,EVRANK);  // must be atom or list
 GATV(z,INT,AN(a),AR(a),AS(a));  // allocate result
 I *av=IAV(a), *zv=IAV(z);
 DQ(AN(z),   // install the requested info
  switch(*av++){
  default: ASSERT(0,EVDOMAIN); break;
  case 0: *zv++=(AFLAG(w)>>AFNJAX)&1; break;
  }
 )
 RETF(z);
}
// a 3!:9 w   noun info


/* binary and hex representation formats differ per J version              */
/* pre J6.01                                                               */
/*    (type, flag, #elements, rank, shape; ravel)                          */
/*    flag is set to 0 for 32 bits and _1 for 64 bits                      */
/* J6.01 and later                                                         */
/*    (flag, type, #elements, rank, shape; ravel)                          */
/*    first byte of flag is                                                */
/*      e0     32 bits, reversed byte order                                */
/*      e1     32 bits, reversed byte order                                */
/*      e2     64 bits, standard byte order                                */
/*      e3     64 bits, reversed byte order                                */
/*      other  pre 601 header                                              */


#define LGWS(d)         ((d)+2)  // LG(WS(d))
#define WS(d)           (((I)1)<<LGWS(d))                 /* word size in bytes              */
#define BH(d)           (4LL<<LGWS(d))               /* # non-shape header bytes in A   */
#define BF(d,a)         ((C*)(a)        )       /* flag                            */
#define BT(d,a)         ((C*)(a)+  WS(d))       /* type                            */
#define BTX(d,pre601,a) ((C*)(a)+  WS(d)*!pre601)
#define BN(d,a)         ((C*)(a)+(2LL<<LGWS(d)))       /* # elements in ravel             */
#define BR(d,a)         ((C*)(a)+(3LL<<LGWS(d)))       /* rank                            */
#define BS(d,a)         ((C*)(a)+(4LL<<LGWS(d)))       /* shape                           */
#define BV(d,a,r)       (BS(d,a)+((r)<<LGWS(d)))     /* value                           */
#define BU              (C_LE ? 1 : 0)


static I bsize(J jt,B d,B tb,I t,I n,I r,I*s){I c,k,m,w,z;
 w=WS(d);
 z=BH(d)+w*r;
 if(t&BIT){
  c=r?s[r-1]:1; m=c?n/c:0; 
  R z+w*m*((c+w*BB-1)/(w*BB));
 }else{
  k=t&INT+SBT+BOX+XNUM?w:t&RAT?w+w:bp(t); 
  R z+((n*k+(tb&&t&LAST0)+w-1)&(-w));
}}   /* size in byte of binary representation */


/* n:  # of words                */
/* v:  ptr to result             */
/* u:  ptr to argument           */
/* bv: 1 iff v is little-endian  */
/* bu: 1 iff u is little-endian  */
/* dv: 1 iff v is 64-bit         */
/* du: 1 iff u is 64-bit         */

#define MVCS(a,b,c,d)  (8*(a)+4*(b)+2*(c)+(d))

static B jtmvw(J jt,C*v,C*u,I n,B bv,B bu,B dv,B du){C c;
 switch((dv?8:0)+(du?4:0)+(bv?2:0)+bu){
  case MVCS(0,0,0,0): MC(v,u,n*4);                             break;
  case MVCS(0,0,0,1): DO(n, DO(4, v[3-i]=u[i];); v+=4; u+=4;); break;
  case MVCS(0,0,1,0): DO(n, DO(4, v[3-i]=u[i];); v+=4; u+=4;); break;
  case MVCS(0,0,1,1): MC(v,u,n*4);                             break;
  case MVCS(0,1,0,0): DO(n, c=127<(UC)u[0]?CFF:C0; DO(4, ASSERT(c==u[  i],EVLIMIT); v[i]=u[4+i];); v+=4; u+=8;); break;
  case MVCS(0,1,0,1): DO(n, c=127<(UC)u[7]?CFF:C0; DO(4, ASSERT(c==u[7-i],EVLIMIT); v[i]=u[3-i];); v+=4; u+=8;); break;
  case MVCS(0,1,1,0): DO(n, c=127<(UC)u[0]?CFF:C0; DO(4, ASSERT(c==u[3-i],EVLIMIT); v[i]=u[7-i];); v+=4; u+=8;); break;
  case MVCS(0,1,1,1): DO(n, c=127<(UC)u[7]?CFF:C0; DO(4, ASSERT(c==u[4+i],EVLIMIT); v[i]=u[  i];); v+=4; u+=8;); break;
  case MVCS(1,0,0,0): DO(n, c=127<(UC)u[0]?CFF:C0; DO(4, v[  i]=c; v[4+i]=u[i];); v+=8; u+=4;); break;
  case MVCS(1,0,0,1): DO(n, c=127<(UC)u[3]?CFF:C0; DO(4, v[3-i]=c; v[7-i]=u[i];); v+=8; u+=4;); break;
  case MVCS(1,0,1,0): DO(n, c=127<(UC)u[0]?CFF:C0; DO(4, v[7-i]=c; v[3-i]=u[i];); v+=8; u+=4;); break;
  case MVCS(1,0,1,1): DO(n, c=127<(UC)u[3]?CFF:C0; DO(4, v[4+i]=c; v[  i]=u[i];); v+=8; u+=4;); break;
  case MVCS(1,1,0,0): MC(v,u,n*8);                             break;
  case MVCS(1,1,0,1): DO(n, DO(8, v[7-i]=u[i];); v+=8; u+=8;); break;
  case MVCS(1,1,1,0): DO(n, DO(8, v[7-i]=u[i];); v+=8; u+=8;); break;
  case MVCS(1,1,1,1): MC(v,u,n*8);                             break;
 }
 R 1;
}    /* move n words from u to v */

static C*jtbrephdr(J jt,B b,B d,A w,A y){A q;I f,r;I extt = UNSAFE(AT(w));
 q=(A)AV(y); r=AR(w); f=0;
 RZ(mvw(BF(d,q),(C*)&f,    1L,b,BU,d,SY_64)); *CAV(y)=d?(b?0xe3:0xe2):(b?0xe1:0xe0);
 RZ(mvw(BT(d,q),(C*)&extt,1L,b,BU,d,SY_64));
 RZ(mvw(BN(d,q),(C*)&AN(w),1L,b,BU,d,SY_64));
 RZ(mvw(BR(d,q),(C*)&r,1L,b,BU,d,SY_64));  // r is an I
 RZ(mvw(BS(d,q),(C*) AS(w),r, b,BU,d,SY_64));
 R BV(d,q,r);
}

static A jtbreps(J jt,B b,B d,A w){A q,y,z,*zv;C*v;I c=0,kk,m,n;P*wp;
 wp=PAV(w);
 n=1+sizeof(P)/SZI; kk=WS(d);
 GATV0(z,BOX,n,1); zv=AAV(z);
 GATV0(y,LIT,bsize(jt,d,1,INT,n,AR(w),AS(w)),1);
 v=brephdr(b,d,w,y);
 RZ(mvw(v,(C*)&c,1L,BU,b,d,SY_64));  /* reserved for flag */
 zv[0]=y; m=AN(y);
 RZ(zv[1]=q=brep(b,d,SPA(wp,a))); RZ(mvw(v+  kk,(C*)&m,1L,b,BU,d,SY_64)); m+=AN(q);
 RZ(zv[2]=q=brep(b,d,SPA(wp,e))); RZ(mvw(v+2*kk,(C*)&m,1L,b,BU,d,SY_64)); m+=AN(q);
 RZ(zv[3]=q=brep(b,d,SPA(wp,i))); RZ(mvw(v+3*kk,(C*)&m,1L,b,BU,d,SY_64)); m+=AN(q);
 RZ(zv[4]=q=brep(b,d,SPA(wp,x))); RZ(mvw(v+4*kk,(C*)&m,1L,b,BU,d,SY_64));
 R raze(z);
}    /* 3!:1 w for sparse w */

A jtbrep(J jt,B b,B d,A w){A q,*wv,y,z,*zv;C*u,*v;I e,klg,kk,m,n,t;
 RZ(w);
 e=n=AN(w); t=UNSAFE(AT(w)); u=CAV(w); klg=bplg(t); kk=WS(d);
 if(t&SPARSE)R breps(b,d,w);
 GATV0(y,LIT,bsize(jt,d,1,t,n,AR(w),AS(w)),1);
 v=brephdr(b,d,w,y);
 if(t&DIRECT)switch(CTTZ(t)){
  case SBTX:
  case INTX:  RZ(mvw(v,u,n,  b,BU,d,SY_64)); R y;
  case FLX:   RZ(mvw(v,u,n,  b,BU,1,1    )); R y;
  case CMPXX: RZ(mvw(v,u,n+n,b,BU,1,1    )); R y;
  default:
   // 1- and 2-byte C4T types, all of which have LAST0.  We need to clear the last
   // bytes, because the datalength is rounded up in bsize, and thus there are
   // up to 3 words at the end of y that will not be copied to.  We clear them to
   // 0 to provide repeatable results.
   // Make sure there is a zero byte if the string is empty
   {I suffsize = MIN(4*SZI,(CAV(y)+AN(y))-(C*)v);  // len of area to clear to 0 
   memset((CAV(y)+AN(y))-suffsize,C0,suffsize);   // clear suffix
   MC(v,u,n<<klg); R y;}      // copy the valid part of the data
 }
 if(t&RAT){e+=n; GATV0(q,XNUM,e,1); MC(AV(q),u,n<<klg);}
 else     RZ(q=1<AR(w)?ravel(w):w);
 m=AN(y); wv=AAV(w); 
 GATV0(z,BOX,1+e,1); zv=AAV(z); 
 *zv++=y;
 DO(e, RZ(*zv++=q=brep(b,d,wv[i])); RZ(mvw(v+i*kk,(C*)&m,1L,b,BU,d,SY_64)); m+=AN(q););
 R raze(z);
}    /* b iff reverse the bytes; d iff 64-bit */

static A jthrep(J jt,B b,B d,A w){A y,z;C c,*hex="0123456789abcdef",*u,*v;I n,s[2];
 RZ(y=brep(b,d,w));
 n=AN(y); s[0]=n>>LGWS(d); s[1]=2*WS(d); 
 GATVR(z,LIT,2*n,2,s);  
 u=CAV(y); v=CAV(z); 
 DO(n, c=*u++; *v++=hex[(c&0xf0)>>4]; *v++=hex[c&0x0f];); 
 RETF(z);
}

F1(jtbinrep1){RZ(w); ASSERT(NOUN&AT(w),EVDOMAIN); R brep(BU,SY_64,w);}  /* 3!:1 w */
F1(jthexrep1){RZ(w); ASSERT(NOUN&AT(w),EVDOMAIN); R hrep(BU,SY_64,w);}  /* 3!:3 w */

F2(jtbinrep2){I k;
 RZ(a&&w);
 RE(k=i0(a)); if(10<=k)k-=8;
 ASSERT(k<=0||k<=3,EVDOMAIN);
 R brep((B)(k&1),(B)(2<=k),w);
}    /* a 3!:1 w */

F2(jthexrep2){I k;
 RZ(a&&w); 
 RE(k=i0(a)); if(10<=k)k-=8;
 ASSERT(k<=0||k<=3,EVDOMAIN);
 R hrep((B)(k&1),(B)(2<=k),w);
}    /* a 3!:3 w */


static S jtunh(J jt,C c){
 if('0'<=c&&c<='9')R c-'0';
 if('a'<=c&&c<='f')R 10+c-'a';
 ASSERT(0,EVDOMAIN);
}

static F1(jtunhex){A z;C*u;I c,n;UC p,q,*v;
 RZ(w);
 c=*(1+AS(w));
 ASSERT(c==8||c==16,EVLENGTH);  
 n=AN(w)>>1; u=CAV(w);
 GATV0(z,LIT,n,1); v=UAV(z);
 DO(n, p=*u++; q=*u++; *v++=16*unh(p)+unh(q););
 RE(z); RETF(z);
}

static A jtunbinr(J jt,B b,B d,B pre601,I m,A w){A y,z;C*u=(C*)w,*v;I e,j,kk,n,p,r,*s,t,*vv;
 ASSERT(m>BH(d),EVLENGTH);
 RZ(mvw((C*)&t,BTX(d,pre601,w),1L,BU,b,SY_64,d));
 RZ(mvw((C*)&n,BN(d,w),1L,BU,b,SY_64,d));
 RZ(mvw((C*)&r,BR(d,w),1L,BU,b,SY_64,d)); 
 kk=WS(d); v=BV(d,w,r);
 ASSERT((t==LOWESTBIT(t))&&t&(B01|INT|FL|CMPX|BOX|XNUM|RAT|LIT|C2T|C4T|SB01|SLIT|SINT|SFL|SCMPX|SBOX|SBT),EVDOMAIN);
 ASSERT(0<=n,EVDOMAIN);
 ASSERT(0<=r&&r<=RMAX,EVRANK);
 p=bsize(jt,d,0,t,n,r,0L); e=t&RAT?n+n:t&SPARSE?1+sizeof(P)/SZI:n; 
 ASSERT(m>=p,EVLENGTH);
 if(t&DENSE){GA(z,t,n,r,0)}else{GASPARSE(z,t,n,r,(I*)0)} s=AS(z);
 RZ(mvw((C*)s,BS(d,w),r,BU,b,SY_64,d)); 
 j=1; DO(r, ASSERT(0<=s[i],EVLENGTH); if(t&DENSE)j*=s[i];); 
 ASSERT(j==n,EVLENGTH);
 if(t&BOX+XNUM+RAT+SPARSE){GATV0(y,INT,e,1); vv=AV(y); RZ(mvw((C*)vv,v,e,BU,b,SY_64,d));}
 if(t&BOX+XNUM+RAT){A*zv=AAV(z);I i,k=0,*iv;
  RZ(y=indexof(y,y)); iv=AV(y);
  for(i=0;i<e;++i){
   j=vv[i]; 
   ASSERT(0<=j&&j<m,EVINDEX);
   if(i>iv[i])zv[i]=zv[iv[i]];
   else{while(k<e&&j>=vv[k])++k; zv[i]=rifvs(unbinr(b,d,pre601,k<e?vv[k]-j:m-j,(A)(u+j)));}
 }}else if(t&SPARSE){P*zp=PAV(z);
  j=vv[1]; ASSERT(0<=j&&j<m,EVINDEX); SPB(zp,a,unbinr(b,d,pre601,vv[2]-j,(A)(u+j)));
  j=vv[2]; ASSERT(0<=j&&j<m,EVINDEX); SPB(zp,e,unbinr(b,d,pre601,vv[3]-j,(A)(u+j)));
  j=vv[3]; ASSERT(0<=j&&j<m,EVINDEX); SPB(zp,i,unbinr(b,d,pre601,vv[4]-j,(A)(u+j)));
  j=vv[4]; ASSERT(0<=j&&j<m,EVINDEX); SPB(zp,x,unbinr(b,d,pre601,m    -j,(A)(u+j)));
 }else if(n)switch(CTTZNOFLAG(t)){
  case B01X:  {B c,*zv=BAV(z); DO(n, c=v[i]; ASSERT(c==C0||c==C1,EVDOMAIN); zv[i]=c;);} break; 
  case SBTX:
  case INTX:  RZ(mvw(CAV(z),v,n,  BU,b,SY_64,d)); break;
  case FLX:   RZ(mvw(CAV(z),v,n,  BU,b,1,    1)); break;
  case CMPXX: RZ(mvw(CAV(z),v,n+n,BU,b,1,    1)); break;
  default:   e=n<<bplg(t); ASSERTSYS(e<=allosize(z),"unbinr"); MC(CAV(z),v,e);
 }
 RE(z); RETF(z);
}    /* b iff reverse the bytes; d iff argument is 64-bits */

F1(jtunbin){A q;B b,d;C*v;I c,i,k,m,n,r,t;
 RZ(w);
 ASSERT(LIT&AT(w),EVDOMAIN);
 if(2==AR(w))RZ(w=unhex(w));
 ASSERT(1==AR(w),EVRANK);
 m=AN(w);
 ASSERT(m>=8,EVLENGTH);
 q=(A)AV(w);
 switch(*CAV(w)){
  case (C)0xe0: R unbinr(0,0,0,m,q);
  case (C)0xe1: R unbinr(1,0,0,m,q);
  case (C)0xe2: R unbinr(0,1,0,m,q);
  case (C)0xe3: R unbinr(1,1,0,m,q);
 }
 /* code to handle pre 601 headers */
 d=1; v=8+CAV(w); DO(8, if(CFF!=*v++){d=0; break;});       /* detect 64-bit        */
 ASSERT(m>=1+BH(d),EVLENGTH);
 b=0;
 if(!mvw((C*)&t,BTX(d,1,q),1L,BU,0,SY_64,d)){RESETERR; b=1;} /* detect reverse bytes */
 if(!mvw((C*)&n,BN(d,q),1L,BU,0,SY_64,d)){RESETERR; b=1;}
 if(!mvw((C*)&r,BR(d,q),1L,BU,0,SY_64,d)){RESETERR; b=1;}
 b=b||!(t&NOUN&&0<=n&&0<=r&&(r||1==n)&&m>=BH(d)+r*WS(d));
 if(t&DENSE){
  v=BS(d,q); c=1;
  for(i=0;!b&&i<r;++i){
   if(!mvw((C*)&k,v,1L,BU,0,SY_64,d)){RESETERR; b=1;}
   v+=WS(d); c*=k;
   if(!(0<=k&&(!n||0<=c&&k<=n&&c<=n)))b=1;
  }
  b=b||n!=c;
 }
 R unbinr(b,d,1,m,q);
}    /* 3!:2 w, inverse for binrep/hexrep */


F2(jtic2){A z;I j,m,n,p,*v,*x,zt;I4*y;UI4*y1;S*s;U short*u;
 RZ(a&&w);
 ASSERT(1>=AR(w),EVRANK);
 n=AN(w);
 RE(j=i0(a));
#if SY_64
 ASSERT(ABS(j)<=4,EVDOMAIN);
#else
 ASSERT(ABS(j)<=2,EVDOMAIN);
#endif
// long way p=4==j||-4==j?4:3==j||-3==j?8:2==j||-2==j?4:2;
 p=ABS(j); p+=(I )(p==0)-((p&4)>>1);   // p becomes (|j){1 1 2 3 2
 if(0<j){m=n<<p; zt=LIT; if(!(INT&AT(w)))RZ(w=cvt(INT,w));}
 else   {m=n>>p; zt=INT; ASSERT(!n||LIT&AT(w),EVDOMAIN); ASSERT(!(n&((((I)1)<<p)-1)),EVLENGTH);} 
 GA(z,zt,m,1,0); v=AV(z); x=AV(w); 
 switch(j){
  default: ASSERT(0,EVDOMAIN);
  case -4: y1=(UI4*)x;    DO(m, *v++=    *y1++;); {RETF(z);}
  case  4: y1=(UI4*)v;    DO(n, *y1++=(UI4)*x++;); {RETF(z);}
  case -3: ICPY(v,x,m); {RETF(z);}
  case  3: MC(v,x,m);   {RETF(z);}
  case -2: y=(I4*)x;      DO(m, *v++=    *y++;); {RETF(z);}
  case  2: y=(I4*)v;      DO(n, *y++=(I4)*x++;); {RETF(z);}
  case -1: s=(S*)x;       DO(m, *v++=    *s++;); {RETF(z);}
  case  1: s=(S*)v;       DO(n, *s++=(S) *x++;); {RETF(z);}
  case  0: u=(U short*)x; DO(m, *v++=    *u++;); {RETF(z);}
}}

F2(jtfc2){A z;D*x,*v;I j,m,n,p,zt;float*s;
 RZ(a&&w);
 ASSERT(1>=AR(w),EVRANK);
 n=AN(w);
 RE(j=i0(a));
 p=2==j||-2==j?LGSZD:2;
 if(0<j){m=n<<p; zt=LIT; if(!(FL&AT(w)))RZ(w=cvt(FL,w));}
 else   {m=n>>p; zt=FL; ASSERT(!n||LIT&AT(w),EVDOMAIN); ASSERT(!(n&((((I)1)<<p)-1)),EVLENGTH);} 
 GA(z,zt,m,1,0); v=DAV(z); x=DAV(w);
 switch(j){
  default: ASSERT(0,EVDOMAIN);
  case -2: MC(v,x,n); {RETF(z);}
  case  2: MC(v,x,m); {RETF(z);}
  case -1: s=(float*)x; DO(m, *v++=       *s++;); {RETF(z);}
  case  1: s=(float*)v; DO(n, *s++=(float)*x++;); {RETF(z);}
}}


static B jtisnanq(J jt,A w){A q,*u,x,x1,*xv,y,*yv;D*v;I m,n,t,top;
 RZ(w);
 GATV0(x,INT,BOX&AT(w)?2*AN(w):1,1); xv=AAV(x);
 *xv=w; top=1;
 while(top){
  --top; y=xv[top]; n=AN(y); t=AT(y);
  if(t&FL+CMPX){v=DAV(y); DO(t&CMPX?n+n:n, if(_isnan(*v++))R 1;);}
  else if(t&BOX){
   m=top+n; yv=AAV(y); 
   if(m>AN(y)){GATV0(x1,INT,2*m,1); u=AAV(x1); ICPY(u,xv,top); fa(x); x=x1; xv=u;}
   u=xv+top; DO(n, q=yv[i]; if(AT(q)&FL+CMPX+BOX)*u++=q;); top=u-xv;
 }}
 R 0;
}

F1(jtisnan){A*wv,z;B*u;D*v;I n,t;
 RZ(w);
 n=AN(w); t=AT(w);
 ASSERT(t&DENSE,EVNONCE);
 GATV(z,B01,n,AR(w),AS(w)); u=BAV(z);
 if     (t&FL  ){v=DAV(w); DO(n, *u++=_isnan(*v++););}
 else if(t&CMPX){v=DAV(w); DO(n, *u++=_isnan(*v)||_isnan(*(v+1)); v+=2;);}
 else if(t&BOX ){wv=AAV(w);  DO(n, *u++=isnanq(wv[i]);); RE(0);}
 else memset(u,C0,n);
 RETF(z);
}


F1(jtbit1){A z;B*wv;BT*zv;I c,i,j,n,p,q,r,*s;UI x,y;
 RZ(w);
 if(!(B01&AT(w)))RZ(w=cvt(B01,w));
 n=AN(w); r=AR(w); wv=BAV(w); s=AS(w);
 GA(z,BIT,n,AR(w),AS(w)); zv=(BT*)AV(z);
 if(!r)*zv=*wv?'\200':0;
 else if(n){
  c=8*SZI; 
  i=s[r-1]; r= p=n/i; q=i/c; r=i-c*q;
  for(i=0;i<p;++i){
   for(j=0;j<q;++j){
    x=0; y=1+(UI)IMAX; 
    DO(c, if(*wv++)x^=y; y>>=1;); 
    *zv++=x;
   }
    x=0; y=1+(UI)IMAX; 
    DO(r, if(*wv++)x^=y; y>>=1;); 
    *zv++=x;
  }
 }
 R z;
}    /* convert byte booleans to bit booleans */

F2(jtbit2){
 ASSERT(0,EVNONCE);
}    /* convert byte booleans to bit booleans */

/* Copyright 2014, Jsoftware Inc.  All rights reserved. */
// datetime epoch routines

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#define MINY  1800  // minimum year allowed
#define MAXY  2200  // maximum year allowed
#define MIND  (I)73048    // number of days from epoch (20000101) to minimum day allowed 18000101
#define MAXD  (I)73414    // number of days from epoch (20000101) to first day not allowed 22010101 - must be >= MIND for range calculation to be accurate
#define BASE  946684800
#define NANOS 1000000000LL
#define SECS  86400

// e from yyyymmddhhmnss.  The argument is assumed to be well-formed
static I eft(I n,UI* e,UI* t)
{
#if SY_64
	I i; UI4 kk,M,Y,D; UI k,hh,mm,ss;  // use unsigned to make / and % generate better code
	for(i=0;i<n;++i){
	 k=t[i];  // read the yyyymmddhhmnss value
	 ss=k%100U; k=k/100U;  // ss yyyymmddhhmn
	 mm=k%100U; k=k/100U;  // ss mn yyyymmddhh
	 hh=k%100U; kk=(UI4)(k/100U);  // ss mn hh yyyymmdd.  yyyymmdd fits in UI4, so switch to that (faster /, %)
	 D=kk%100U; kk=kk/100U;  // ss mn hh D yyyymm
	 M=kk%100U;   // ss mn hh D M
  Y=kk/100U;  // ss mn hh D M Y

  // Now calculate number of days from epoch.  First reorder months so that the irregular February comes last, i. e. make the year start Mar 1
  UI4 janfeb=(I4)(M-3)>>(32-1);   // -1 if jan/feb
  Y+=janfeb; M+=janfeb&12;  // if janfeb, subtract 1 from year and add 12 to month
  // Add in leap-years (since the year 0, for comp. ease).  Year 2000 eg, which starts Mar 1, is a leap year and has 1 added to its day#s (since they come after Feb 29)
  D+=Y>>2;
  // Gregorian correction.  Since it is very unlikely we will encounter a date that needs correcting, we use an IF
  if((UI4)(Y-1901)>(UI4)(2100-1901)){  // date is outside 1901-2099
   D+=(((Y/100)>>2)-(Y/100))-((2000/400)-(2000/100));  // 1900 2100 2200 2300 2500 etc are NOT leapyears.  Create correction from Y2000 count
  }
  // Add in extra days for earlier 31-day months in this adjusted year (so add 0 in March)
  D+=(0x765544322110000>>(4*M))&0xf;  // starting with month 0, this is x x x 0 1 1 2 2 3 4 4 5 5 6 7
  // Calculate day from YMD.  Bias from day# of 20000101, accounting for leap-years from year 0 to that date.  Note 20000101 is NOT in a leapyear - it is in year 1999 here
  // The bias includes: subtracting 1 from day#; subtracting 1 from month#; Jan/Feb of 1999; Gregorian leapyears up to 2000
  I temp=(I)(365*Y + 30*M + D) - 730531;  // day# from epoch - can be negative
  // Combine everythine into one # and store
 	e[i]=(NANOS*24LL*60LL*60LL)*temp + (NANOS*3600LL)*hh + (NANOS*60LL)*mm + NANOS*ss;  // eschew Horner's Rule because of multiply latency
	}
#endif
	return 0;
}

#if 0 // obsolete 
// iso 8601 from e (epoch date time)
// sz - separator , or . and zulu 'Z' or ' '
static I sfe(I rows,I cols,char* s,I* e,char* sz)
{
	I k; int i,M,v,d,j,g,m,t,y,hh,mm,ss; char b[1000];char* q;
	for(i=0;i<rows;++i)
	{
		k= e[i];
		M=k%NANOS;
		k=k/NANOS;
		v=k%SECS;
		k= k/SECS;
		if(e[i]<0)
		{
			if(M<0)
			{
				v=v-1;
				M=M+NANOS;
				if(M<0) M=-M;
			}
			if(v<0)
			{
				k=k-1;
				v=v+24*60*60;
				if(v<0) v=-v;
			}
		}
		memset(b,0,(int)cols+1);
		memset(s,' ',(int)cols);		
		j=(int)k+2451545;
		g=(int)floor(3*floor((4*j+274277)/146097)/4)-38;
		j+=1401+g;
		t=4*j+3;
		y=(int)floor(t/1461);
		t=(t%1461)>>2;
		m=(int)floor((t*5+461)/153);
		d=(int)floor(((t*5+2)%153)/5);
		if (m>12) {
		  y++;
		  m-=12;
		}
		y=y-4716;
		++d;

		hh= v/3600;
		v= v%3600;
		mm= v/60;
		ss= v%60;
		sprintf(b,"%04d-%02d-%02dT%02d:%02d:%02d",y,m,d,hh,mm,ss);
		q=b+strlen(b);
		*q++=sz[0];
		sprintf(q,"%09d",(int)M);
		if(y>=MINY && y<=MAXY)
			strncpy(s,b,cols);
		else
			s[0]='?';
		if(sz[1]=='Z') s[cols-1]='Z';
		s+=cols;
	}
	return 0;
}
#endif

static UC char2tbl[200] = {
'0','0' , '0','1' , '0','2' , '0','3' , '0','4' , '0','5' , '0','6' , '0','7' , '0','8' , '0','9' ,
'1','0' , '1','1' , '1','2' , '1','3' , '1','4' , '1','5' , '1','6' , '1','7' , '1','8' , '1','9' ,
'2','0' , '2','1' , '2','2' , '2','3' , '2','4' , '2','5' , '2','6' , '2','7' , '2','8' , '2','9' ,
'3','0' , '3','1' , '3','2' , '3','3' , '3','4' , '3','5' , '3','6' , '3','7' , '3','8' , '3','9' ,
'4','0' , '4','1' , '4','2' , '4','3' , '4','4' , '4','5' , '4','6' , '4','7' , '4','8' , '4','9' ,
'5','0' , '5','1' , '5','2' , '5','3' , '5','4' , '5','5' , '5','6' , '5','7' , '5','8' , '5','9' ,
'6','0' , '6','1' , '6','2' , '6','3' , '6','4' , '6','5' , '6','6' , '6','7' , '6','8' , '6','9' ,
'7','0' , '7','1' , '7','2' , '7','3' , '7','4' , '7','5' , '7','6' , '7','7' , '7','8' , '7','9' ,
'8','0' , '8','1' , '8','2' , '8','3' , '8','4' , '8','5' , '8','6' , '8','7' , '8','8' , '8','9' ,
'9','0' , '9','1' , '9','2' , '9','3' , '9','4' , '9','5' , '9','6' , '9','7' , '9','8' , '9','9'
};

static I nanopowers[9] = {100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1};

// Convert nanosec to ISO8601
// w is input array, decimalpt is character to use if there are fractional sec, zuluflag is timezone character
// prec is -1 for date only, 0 for integer seconds, 1-9 for that many fractional seconds places
// prec of 7*SZI-21 means 'produce 7 ints per input time'
static A sfe(J jt,A w,I prec,UC decimalpt,UC zuluflag){
#if SY_64
	UI k; UI4 ymd,E,N,M,HMS,d,j,g,m,t,y;I i;A z;  // unsigned for faster / %
 // Validate input.  We will accept FL input, but it's not going to have nanosecond precision
 RZ(w=vi(w));  // convert to INT
 // Figure out size of result. 10 for date, 9 for time, 1 for binary point (opt), 1 for each fractional digit (opt), 1 for timezone
 I linelen=(10+9)-((prec>>(BW-1))&9)+prec+(prec!=0)+(zuluflag=='Z');  // bytes per line of result: 20, but 10 if no date, plus one per frac digit, plus decimal point if any frac digits, 1 if Z
   // if we are running for 6!:15, linelen will come out 56 and the store will be 7 INTs
 // Allocate result area, one row per input value
 GATV0(z,LIT,AN(w)*linelen,AR(w)+1) MCISH(AS(z),AS(w),AR(w)) AS(z)[AR(w)]=linelen==7*SZI?7:linelen;
 // If the result will be INT, make it so
 if(linelen==56){AT(z)=INT; AN(z)>>=LGSZI;}
 if(AN(w)==0)RETF(z);  // handle empty return
 I rows=AN(w);  // number of rows to process
 I *e=IAV(w);  // pointer to nanosecond data
 C *s=CAV(z);  // pointer to result

 // Loop for each time
	for(i=0;i<rows;++i, s+=linelen){
  // fetch the time.  If it is negative, add days amounting to the earliest allowed time so that the modulus calculations can always
  // be positive to get hmsn.  We will add the days back for all the day calculations, since they are in the Julian epoch anyway
		k= e[i] + ((e[i]>>(BW-1))&(MIND*(I)24*(I)3600*(I)NANOS));  // ymdHMSN
  if((UI)k>=(UI)(MAXD*(I)24*(I)3600*(I)NANOS)){if(linelen==7*SZI)DO(7, ((I*)s)[i]=0;)else{DO(linelen, s[i]=' ';) s[0]='?';} continue;}  // input too low - probably DATAFILL(=IMIN) - return fast unknown
    // we use the fact that MAXD>MIND to get the out-of-bounds test right
  N=(UI4)(k%NANOS); k=k/NANOS;  // can't fast-divide by more than 32 bits.  k=ymdHMS N=nanosec
		HMS=(UI4)(k%((I)24*(I)3600));	ymd=(UI4)(k/((I)24*(I)3600));
  ymd-=((e[i]>>(BW-1))&MIND);  // remove negative-year bias if given
  E=HMS%60; HMS/=60;  // sec
  M=HMS%60; HMS/=60;  // minutes; HMS now=hours
  // Now the leap-year calculations.  We follow Richards at https://en.wikipedia.org/wiki/Julian_day#Julian_or_Gregorian_calendar_from_Julian_day_number
		j=ymd+2451545;  // Julian day number, by adding day-from-epoch to JD of epoch
		g=((3*((4*j+274277)/146097))>>2)-38;  // Gregorian correction for leapyears from year 0
		j+=1401+g;  // Julian day, plus 1401 (Julian leapyears to year 0), plus Gregorian leapyears
  // now find position within 1461-day 4-year cycle
		t=4*j+3;   // temp
		y=t/1461-4716;  // year number from Julian epoch, plus starting year of Julian epoch
		t=(t%1461)>>2;  // day number within year, which starts Mar 1
		m=(t*5+461)/153;  // razzmatazz to convert day# to month, 3-14
// Richards version		d=((t*5+2)%153)/5;
  d=(t+((0x444332221100000>>(m<<2))&0xf))%31+1;  // # days   start-of-month must advance to be on 31-day multiple, by month: x x x 0(Mar) 0(Apr) 1 1 2 2 2 3 3 4 4 4
  I4 janfeb=(I4)(12-m)>>(32-1); y-=janfeb; m-=janfeb&12;  // move jan-feb into next year number
  // Now write the result yyyy-mm-ddThh:mm:ss.nnnnnnnnn
#if 0
    // This is the straightforward way to write the result.  I have gone to a different method because this version releases 32 integer multiplies,
    // of which 8 have a chained dependency which might amount to 32 clocks.  I'm not sure the whole loop will take 32 clocks - it'll be close -
    // so I have gone to a version that doesn't use the multiply unit as much
   s[3]='0'+y%10; y/=10; s[2]='0'+y%10; y/=10; s[1]='0'+y%10; s[0]='0'+y/10;
   s[4]='-'; s[5]='0'+m/10; s[6]='0'+m%10;
   s[7]='-'; s[8]='0'+d/10; s[9]='0'+d%10;
   s[10]='T'; s[11]='0'+HMS/10; s[12]='0'+HMS%10;
   s[13]='-'; s[14]='0'+M/10; s[15]='0'+M%10;
   s[16]='-'; s[17]='0'+E/10; s[18]='0'+E%10;
   s[19]='.'; DQ(8, s[21+i]='0'+N%10; N/=10;) s[20]='0'+N;
#endif
  if(linelen!=7*SZI){  // normal case of LIT output
   // Store bytes two at a time using a lookup.  The lookup fits in 4 cache lines & so should be available for most of the loop.
   // (actually, at this time only the values 0-31 will be used much, just 1 cache line)
   // This uses the load/store unit heavily but it's OK if it backs up, since it is idle during the first half of the loop
   // This ends with 5 dependent integer multiplies; hope that's OK
   *(S*)(s+0) = ((S*)char2tbl)[y/100]; *(S*)(s+2) = ((S*)char2tbl)[y%100];
   s[4]='-'; *(S*)(s+5) = ((S*)char2tbl)[m];
   s[7]='-'; *(S*)(s+8) = ((S*)char2tbl)[d];
   if(linelen>(10+1)){  // if time requested...  (remember timezone)
    s[10]='T'; *(S*)(s+11) = ((S*)char2tbl)[HMS];
    s[13]=':'; *(S*)(s+14) = ((S*)char2tbl)[M];
    s[16]=':'; *(S*)(s+17) = ((S*)char2tbl)[E];
    if(linelen>(19+1)){  // if fractional nanosec requested
     s[19]=decimalpt;
     // We have to store a variable number of high-order digits.  We will format all 9 digits and optionally
     // store what we want to keep.  To reduce the length of the multiply chain we split the nanos into 
     // NOTE we do not round the nanoseconds
     UI4 nano4=N/100000; N%=100000;   // reduce dependency
     if(linelen>24)DQ(5, I sdig=N%10; N/=10; if(linelen>24+i)s[24+i]=(C)('0'+sdig);)   // the branches should predict correctly after a while
     DQ(4, I sdig=nano4%10; nano4/=10; if(linelen>20+i)s[20+i]=(C)('0'+sdig);)
    }
   }
   if(zuluflag=='Z')s[linelen-1]=zuluflag;
  }else{
   // 6!:15, store results as INTs
   ((I*)s)[0]=y; ((I*)s)[1]=m; ((I*)s)[2]=d; ((I*)s)[3]=HMS; ((I*)s)[4]=M; ((I*)s)[5]=E; ((I*)s)[6]=N;
  }
 }
	RETF(z);
#else
R 0;
#endif
}

#if 0  // obsolete
static int gi(I n, char* q)
{
 char b[10]; I i;
 for(i=0; i<n; ++i)
 {
  if(isdigit(*q)) b[i]=*q++; else return -1;
 }
 if(isdigit(*q)) return -1;
 b[i]=0;
 return (int)strtol(b,0,10);
}

// convert iso 8601 to epoch 2000 nanoseconds
// return count of bad conversions
static  I efs(I rows,I cols, char* s,I* e,I* offset,I ignoreoffset)
{
	int Y,M,D,hh,mm,ss,hho,mmo,v,signn;
	I k,i,N,r=0; char b[1000]; char* q; C sign;
	for(i=0;i<rows;++i)
	{
     e[i]=IMIN;
	 if(offset) offset[i]=-1;
	 ++r; // assume failure
	 M=D=1;
	 hh=mm=ss=hho=mmo=0;
	 N=0;
	 q= b;
	 strncpy(q,s,cols);
	 b[cols]= ' '; b[cols+1]= 0;
	 if(-1==(v= gi(4, q))) goto bad; q+= 4;
	 Y= v;
	 if('-'==*q)
	 {
		 ++q;
		 if(-1==(v= gi(2, q))) goto bad; q+=2;
		 M= v;
		 if('-'==*q)
		 {
			 ++q;
			 if(-1==(v= gi(2, q))) goto bad; q+=2;
			 D=v ;
		 }
	}
	if(*q=='T' || (*q==' '&&isdigit(*(q+1))) ) // T or blank allowed delimiter for time fields
	{
		++q;
		if(-1==(v= gi(2, q))) goto bad; q+=2;
		hh=v;
		if(':'==*q)
		{
			++q;
			if(-1==(v= gi(2, q))) goto bad; q+=2;
			mm= v;
			if(':'==*q)
			{
				++q;
				if(-1==(v= gi(2, q))) goto bad; q+=2;
				ss= v;
				if(*q=='.'||*q==',')
				{
					char b[]= "000000000";
					++q;
					for(k=0; k<9; ++k){if(isdigit(*q))b[k]=*q++;  else  break;}
					N=strtol(b,0,10);
				}
			}
		}
		sign= *q;
		signn= (sign=='+')?1:-1;
		if(sign=='+'||sign=='-')
		{
		   ++q;
		   if(-1==(v= gi(2, q))) goto bad; q+=2;
		   hho= v;
		   if(*q==':')
		   {
			++q;
			if(-1==(v= gi(2, q))) goto bad; q+=2;
			mmo= v;
		   }
		   if(!ignoreoffset)
		   {
            hh-= hho*signn;
            mm-= mmo*signn;
		   }
		}
	}
	if(*q=='Z')++q;
	while(' '==*q)++q;
	if(0==*q)
	{
		if(offset!=0) offset[i]= (hho*60+mmo)*signn;
		if(Y>=MINY && Y<=MAXY)
		{
			if(M<3){Y=Y-1;M=M+12;		}
			k= (int)floor(365.25*Y)-(int)floor(Y/100)+(int)floor(Y/400)+(int)floor(30.6*(M+1))+D-730548; // seconds since 2000
			k= 24*60*60*k;
			k= k+(hh*3600)+(mm*60)+ss;
			e[i]=N+NANOS*k;
			--r;
		}
		else
			e[i]=IMIN;
	}
bad:
	s+=cols;
}
return r;
}
#endif

// w is LIT array of ISO strings (rank>0, not empty), result is array of INTs with nanosecond time for each string
// We don't bother to support a boxed-string version because the strings are shorter than the boxes & it is probably just about as good to just open the boxed strings
// prec is -1 (day only) or 0,3,9 for that many fractional digits below seconds
static A efs(J jt,A w,I prec){
#if SY_64
	I i;A z;
 // Allocate result area
 I n; PROD(n,AR(w)-1,AS(w)); GATV(z,INT,n,AR(w)-1,AS(w))
 I strglen=AS(w)[AR(w)-1];
 C *s=CAV(w);  // point to start of first string
 UC afterday=(UC)((~prec)>>8);  //  0x00 if we stop  after the day, 0xff if we continue
	for(i=0;i<n;++i,s+=strglen){
 	UI4 Y,M,D,ss; I4 hh,mm;  // hh,mm are I because they may go negative during TZ adjustment
  // It's OK to overfetch from a string buffer, as long as you don't rely on the contents fetched.  They're padded
  // We will store an invalid byte on top of the character after the end of the string.  We'll be sure to restore it!
  UC savesentinel = s[strglen]; s[strglen]=0;  // install end-of-string marker
  UC *sp=s;  // scan pointer through the string
  // Read/convert two-digit things.  Once we commit to reading digits, we fail if there aren't two of them; so check types first as needed
  // We code this on the assumption that the format is constant throughout, and therefore branches will not be mispredicted after the first loop
#define DOERR {IAV(z)[i]=IMIN; goto err;}
#define ISDIGIT(d) (((UI4)d-(UI4)'0')<=((UI4)'9'-(UI4)'0'))
#define RDTWO(z) if(!ISDIGIT(sp[1]))DOERR z=(UI4)sp[0]*10+((UI4)sp[1]-(UI4)'0')-((UI4)'0'*(UI4)10); if((UI4)z>(UI4)99)DOERR sp+=2;
// same, but use c for the first digit
#define RDTWOC(z) if(!ISDIGIT(sp[1]))DOERR z=(UI4)c*10+((UI4)sp[1]-(UI4)'0')-((UI4)'0'*(UI4)10); if((UI4)z>(UI4)99)DOERR sp+=2; c=*sp;
  UI N=0;  // init nanosec accum to 0
  // throughout this stretch we may have c set to 'next character'
  UC c=*sp;
  RDTWOC(Y); RDTWOC(M); Y=100*Y+M;  // fetch YYYY.  M is a temp
  if((UI4)(Y-MINY)>(UI4)(MAXY-MINY))DOERR
  if(!(c&~' ')){M=D=1; hh=mm=ss=0; goto gottime;}   // YYYY alone.  Default the rest
  if(c=='T'){M=D=1; goto gotdate;}    // YYYYT.  Default MD
  // normal case
  if(c=='-')c=*++sp;  // skip '-' if present
  RDTWOC(M);
  if(!(c&~' ')){D=1; hh=mm=ss=0; goto gottime;}   // YYYY-MM alone.  Default the rest
  if(c=='T'){D=1; goto gotdate;}    // YYYY-MMT.  Default D
  if(c=='-')c=*++sp;  // skip '-' if present
  RDTWOC(D);
  if(!(c&afterday)){hh=mm=ss=0; goto gottime;}   // YYYY-MM-DD alone, or after-day ignored.  Default the rest.  space here is a delimiter
gotdate: ;
  if((c=='T')|(c==' '))c=*++sp;  // Consume the T/sp if present.  It must be followed by HH.  sp as a separator is not ISO 8601
  if(!(c&~' ')){hh=mm=ss=0; goto gottime;}   // YYYY-MM-DDTbb treat this as ending the year, default the rest
  RDTWOC(hh);
  if((c<0x40) & (((I)1<<'+')|((I)1<<'-')|((I)1<<' ')|((I)1<<0))>>c){mm=ss=0; if((c&~' '))goto hittz; goto gottime;}
// obsolete   if(!(sp[0]&~' ')){mm=ss=0; goto gottime;}   // YYYY-MM-DDTHH.  default the rest
// obsolete   if((sp[0]=='+')|(sp[0]=='-')){mm=ss=0; goto hittz;}
  if(c==':')c=*++sp;  // skip ':' if present
  RDTWOC(mm);
  if((c<0x40) & (((I)1<<'+')|((I)1<<'-')|((I)1<<' ')|((I)1<<0))>>c){ss=0; if((c&~' '))goto hittz; goto gottime;}
// obsolete  if(!(sp[0]&~' ')){ss=0; goto gottime;}   // YYYY-MM-DDTHH:MM.  default the rest
// obsolete  if((sp[0]=='+')|(sp[0]=='-')){ss=0; goto hittz;}
  if(c==':')c=*++sp;  // skip ':' if present
  RDTWOC(ss);
  // If the seconds have decimal extension, turn it to nanoseconds.  ISO8601 allows fractional extension on the last time component even if it's not SS, but we don't support that 
  if((c=='.')|(c==',')){
   c=*++sp;  // skip decimal point
   DO(prec, if(!ISDIGIT(c))break; N+=nanopowers[i]*((UI)c-(UI)'0'); c=*++sp;)  // harder than it looks!  We use memory to avoid long carried dependency from the multiply chain
   // discard trailing digits that we are skipping
   while(ISDIGIT(c))c=*++sp;
  }
hittz:
  // Timezone [+-]HH[[:]MM]  or Z
  if((c=='+')|(c=='-')){
   I4 tzisplus=2*(c=='+')-1;   // +1 for +, -1 for -
   c=*++sp;  // skip tz indic
   I4 tzhm; RDTWOC(tzhm);
   // Apply tz adjustment to hours.  This may make hours negative; that's OK
   hh-=tzisplus*tzhm;    // +tz means UTC was advanced by tz hours; undo it
   if(c==':')c=*++sp;  // skip ':' if present
   if(ISDIGIT(c)){
    RDTWOC(tzhm);
    mm-=tzisplus*tzhm;    // same for minutes, may go negative
   }
  }else if(c=='Z')c=*++sp;  // no numbered timezone; skip Zulu timezone if given
  // Verify no significance after end
  while(c){if(c!=' ')DOERR; c=*++sp;}
gottime: ;
  // We have all the components.  Combine Y M D hh mm ss N into nanosec time
  // This copies the computation in eft except that we have N here.  eft uses unsigned vbls for hh,mm, we don't - no problem

  // Now calculate number of days from epoch.  First reorder months so that the irregular February comes last, i. e. make the year start Mar 1
  UI4 janfeb=(I4)(M-3)>>(32-1);   // -1 if jan/feb
  Y+=janfeb; M+=janfeb&12;  // if janfeb, subtract 1 from year and add 12 to month
  // Add in leap-years (since the year 0, for comp. ease).  Year 2000 eg, which starts Mar 1, is a leap year and has 1 added to its day#s (since they come after Feb 29)
  D+=Y>>2;
  // Gregorian correction.  Since it is very unlikely we will encounter a date that needs correcting, we use an IF
  if((UI)(Y-1901)>(2100-1901)){  // date is outside 1901-2099
   D+=(((Y/100)>>2)-(Y/100))-((2000/400)-(2000/100));  // 1900 2100 2200 2300 2500 etc are NOT leapyears.  Create correction from Y2000 count
  }
  // Add in extra days for earlier 31-day months in this adjusted year (so add 0 in March)
  D+=(0x765544322110000>>(4*M))&0xf;  // starting with month 0, this is x x x 0 1 1 2 2 3 4 4 5 5 6 7
  // Calculate day from YMD.  Bias from day# of 20000101, accounting for leap-years from year 0 to that date.  Note 20000101 is NOT in a leapyear - it is in year 1999 here
  // The bias includes: subtracting 1 from day#; subtracting 1 from month#; Jan/Feb of 1999; Gregorian leapyears up to 2000
  I t=(I)(365*Y + 30*M + D) - 730531;  // day# from epoch.  May be negative
  // Combine everything into one # and store
 	IAV(z)[i]=(NANOS*24LL*60LL*60LL)*t + (NANOS*3600LL)*hh + (NANOS*60LL)*mm + NANOS*ss + N;  // eschew Horner's Rule because of multiply latency

err:
  s[strglen]=savesentinel;  // restore end-of-string marker
 }
 RETF(z);
#else
R 0;
#endif
}




// 6!:14 Convert a block of integer yyyymmddHHMMSS to nanoseconds from year 2000
F1(jtinttoe){A z;I n;
 RZ(w);
 n=AN(w);
 ASSERT(SY_64,EVNONCE);
 RZ(w=vi(w));  // verify valid integer
 GATV(z,INT,n,AR(w),AS(w));
 eft(n,IAV(z),IAV(w));
 RETF(z);
}

// 6!:15 Convert a block of nanosecond times to Y M D h m s nanosec
F1(jtetoint){
 RZ(w);
 ASSERT(SY_64,EVNONCE);
 RETF(sfe(jt,w,7*SZI-20,0,0));  // special precision meaning 'store INTs'.  Turns into linelen=56
}

// 6!:16 convert a block of nanoseconds times to iso8601 format.  Result has an extra axis, long enough to hold the result
// Bivalent.  left arg is 3 characters, one to use as the decimal point, one to store just after the value (usually ' ' or 'Z'),
// one for result precision ('d'=date only, '0'-'9' give # fractional digits)
// Default is '. 0'
F2(jtetoiso8601){UC decimalpt,zuluflag;I prec;
 RZ(w);
 ASSERT(SY_64,EVNONCE);
 // If monad, supply defaults; if dyad, audit
 if(AT(w)&NOUN){  // dyad
  ASSERT(AT(a)&LIT,EVDOMAIN);
  ASSERT(AN(a)==3,EVLENGTH);
  ASSERT(AR(a)==1,EVRANK);  // a must be a 3-character list
  decimalpt=CAV(a)[0]; zuluflag=CAV(a)[1];
  // convert precision character to precision to use (_1 for date, 0-9)
  if(CAV(a)[2]=='d')prec=-1; else {prec=CAV(a)[2]-'0'; ASSERT((UI)prec<(UI)10,EVDOMAIN);}
 }else{
  w=a; decimalpt='.'; zuluflag=' '; prec=0;  // monad: switch argument, set defaults
 }
 RETF(sfe(jt,w,prec,decimalpt,zuluflag));
}

// 6!:17 convert a block of iso8601-format strings to nanosecond times.  Result has one INT for each string
// Bivalent.  left arg is 'd', '0', '3', or '9', like 3d digit of 6!:16, default '9'
F2(jtiso8601toe){I prec;
 RZ(w);
 ASSERT(SY_64,EVNONCE);
 // If monad, supply defaults; if dyad, audit
 if(AT(w)&NOUN){  // dyad
  ASSERT(AT(a)&LIT,EVDOMAIN);
  ASSERT(AN(a)==1,EVLENGTH);
  ASSERT(AR(a)<=1,EVRANK);  // a must be a 1-character list or atom
  // convert precision character to precision to use (_1 for date, 0-9)
  if(CAV(a)[0]=='d')prec=-1; else {prec=CAV(a)[0]-'0'; ASSERT((UI)prec<(UI)10,EVDOMAIN); ASSERT(((I)1<<prec)&0x209,EVNONCE);}  // 0 3 9 allowed
 }else{
  w=a; prec=9; // monad: switch argument, set defaults
 }
 ASSERT(AT(w)&LIT,EVDOMAIN);  // must be LIT
 ASSERT(AR(w),EVRANK);    // must not be an atom
 if(!AN(w))RETF(dfs1(w,qq(sc(IMIN),zeroionei[1])));   // return _"1 w on empty w - equivalent
 RETF(efs(jt,w,prec));
}
