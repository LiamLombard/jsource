/* Copyright 1990-2009, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Extern Declarations                                                     */
#include "gemm.h"

extern F1(jtabase1);
extern F1(jtadot1);
extern F1(jtaflag1);
extern F1(jtarep);
extern F1(jtaro);
extern F1(jtarx);
extern F1(jtasgzombq);
extern F1(jtasgzombs);
extern F1(jtassertq);
extern F1(jtasserts);
extern F1(jtaudittdisab);
extern F1(jtbase1);
extern F1(jtbdot);
extern F1(jtbehead);
extern F1(jtbinrep1);
extern F1(jtbit1);
extern F1(jtbitadv);
extern F1(jtbox);
extern F1(jtboxopen);
extern F1(jtboxq);
extern F1(jtboxs);
extern F1(jtbreakfnq);
extern F1(jtbreakfns);
extern F1(jtbsdot);
extern F1(jtbslash);
extern F1(jtca);
extern F1(jtcaro);
extern F1(jtcallback);
extern F1(jtcallbackx);
extern F1(jtcant1);
extern F1(jtcar);
extern F1(jtcasev);
extern F1(jtcatalog);
extern F1(jtcder);
extern F1(jtcderx);
extern F1(jtcdf);
extern F1(jtcdjt);
extern F1(jtcdlibl);
extern F1(jtcdot1);
extern F1(jtcdproc1);
extern F1(jtceil1);
extern F1(jtcerrno);
extern F1(jtconjug);
extern DF1(jtcork1);
extern F1(jtcpufeature);
extern F1(jtcrc1);
extern F1(jtcrccompile);
extern F1(jtctq);
extern F1(jtcts);
extern F1(jtcurtail);
#if !C_CRC32C
extern F1(jtcvt0);
#endif
extern F1(jtdbc);
extern F1(jtdbcall);
extern F1(jtdbcutback);
extern F1(jtdberr);
extern F1(jtdbetx);
extern F1(jtdbjump);
extern F1(jtdbnext);
extern F1(jtdbq);
extern F1(jtdbret);
extern F1(jtdbrr1);
extern F1(jtdbrun);
extern F1(jtdbsig1);
extern F1(jtdbstack);
extern F1(jtdbstackz);
extern F1(jtdbstepinto1);
extern F1(jtdbstepout1);
extern F1(jtdbstepover1);
extern F1(jtdbstopq);
extern F1(jtdbstops);
extern F1(jtdbtrapq);
extern F1(jtdbtraps);
extern F1(jtdecrem);
extern F1(jtdenseit);
extern F1(jtdgrade1);
extern F1(jtdigits10);
extern F1(jtdispq);
extern F1(jtdisps);
extern F1(jtdl);
extern F1(jtdllsymdat);
extern F1(jtdllsymget);
extern F1(jtdllsymset);
extern F1(jtdomainerr1);
extern F1(jtdrep);
extern F1(jtdrx);
extern F1(jtduble);
extern F1(jtdx_test);
extern F1(jtemend);
extern F1(jtevmq);
extern F1(jtevms);
extern F1(jtex);
extern F1(jtexec1);
extern F1(jtexg);
extern F1(jtexpn1);
extern F1(jtfact);
extern F1(jtfactor);
#if !USECSTACK
extern F1(jtfdepadv);
#endif
extern F1(jtfh15);
extern F1(jtfiller);
extern DF1(jtfix);
extern F1(jtfloor1);
extern F1(jtfmt01);
extern F1(jtfmt11);
extern F1(jtfmt21);
extern F1(jtfname);
extern F1(jtfsmvfya);
extern F1(jtfullname);
extern DF1(jtfx);
extern F1(jtfxeach);
extern F1(jtfxeachacv);
extern F1(jtfxx);
extern F1(jtgaussdet);
extern F1(jtgausselm);
extern F1(jtgb_test);
extern F1(jtgemmtune);
extern F1(jtgh15);
extern F1(jtgrade1);
extern F1(jtgroup);
extern F1(jthalve);
extern F1(jthash);
extern F1(jthead);
extern F1(jthexrep1);
extern F1(jthgdiff);
extern F1(jthost);
extern F1(jthostio);
extern F1(jthostne);
extern F1(jticap);
extern F1(jticvt);
extern F1(jtiden);
extern F1(jtidensb);
extern F1(jtiepdoq);
extern F1(jtiepdos);
extern F1(jtiepq);
extern F1(jtieps);
extern F1(jtimmea);
extern F1(jtimmex);
extern F1(jtincrem);
extern A jtintmod2(J,A,I);
extern F1(jtinttoe);
extern F1(jtetoint);
extern F1(jtiota);
extern F1(jtisnan);
extern F1(jtisempty);
extern F1(jtisitems);
extern F1(jtisnotempty);
extern F1(jtjclose);
extern F1(jtjdir);
extern F1(jtjdot1);
extern F1(jtjfatt1);
extern F1(jtjferase);
extern F1(jtjfiles);
extern F1(jtjfperm1);
extern F1(jtjfread);
extern F1(jtjfsize);
extern F1(jtjgetenv);
extern F1(jtjgetx);
extern F1(jtjgetpid);
extern F1(jtjico1);
extern F1(jtjiread);
extern F1(jtjlock);
extern F1(jtjlocks);
extern F1(jtjmkdir);
extern F1(jtnatoms);
extern F1(jtjoff);
extern F1(jtjopen);
extern F1(jtjpr);
extern F1(jtrank);
extern F1(jtjregcomp);
extern F1(jtjregerror);
extern F1(jtjregfree);
extern F1(jtjreghandles);
extern F1(jtjreginfo);
extern F1(jtjunlock);
extern F1(jtjwait);
extern F1(jtlamin1);
extern F1(jtlcg_test);
extern F1(jtlevel1);
extern F1(jtloccre1);
extern F1(jtlocexmark);
extern F1(jtlock1);
extern F1(jtlocmap);
extern F1(jtlocname);
extern F1(jtlocnc);
extern F1(jtlocnl1);
extern F1(jtlocpath1);
extern F1(jtlocsizeq);
extern F1(jtlocsizes);
extern F1(jtlocswitch);
extern F1(jtlogar1);
extern F1(jtlrep);
extern F1(jtlrx);
extern F1(jtmag);
extern F1(jtmap);
extern F1(jtmat);
extern F1(jtmema);
extern F1(jtmemf);
extern F1(jtmemo);
extern F1(jtmemr);
extern F1(jtmemu);
extern F1(jtminv);
extern F1(jtmmaxq);
extern F1(jtmmaxs);
extern F1(jtmr_test);
extern F1(jtmt_test);
extern F1(jtnameref);
extern F1(jtnc);
extern F1(jtnch);
extern F1(jtnegate);
extern F1(jtnfb);
extern F1(jtnfeoutstr);
extern F1(jtnfes);
extern F1(jtnl1);
extern F1(jtnlsym);
extern F1(jtnot);
extern F1(jtnub);
extern F1(jtnubind);
extern F1(jtnubind0);
extern F1(jtnubsieve);
extern F1(jtnubsievesp);
extern DF1(on1);
extern F1(jtonm);
extern F1(jtope);
extern F1(jtoutparmq);
extern F1(jtoutparms);
extern F1(jtparse);
extern F1(jtparsercalls);
extern F1(jtpathchdir);
extern F1(jtpathcwd);
extern F1(jtpathdll);
extern F1(jtpderiv1);
extern F1(jtpeekdata);
extern F1(jtpinv);
extern DF1(jtpix);
extern F1(jtplt);
extern F1(jtpmarea1);
extern F1(jtpmctr);
extern F1(jtpmstats);
extern F1(jtpmunpack);
extern F1(jtpolar);
extern F1(jtpoly1);
extern F1(jtposq);
extern F1(jtposs);
extern F1(jtpparity);
extern F1(jtppq);
extern F1(jtpps);
extern F1(jtprep);
extern F1(jtprime);
extern F1(jtprocarch);
extern F1(jtprocfeat);
extern F1(jtprx);
extern F1(jtqpctr);
extern F1(jtqpfreq);
extern F1(jtqr);
extern F1(jtranking);
extern F1(jtrankle);
extern F1(jtrat);
extern F1(jtravel);
extern F1(jtraze);
extern F1(jtrazeh);
extern F1(jtrazein);
extern F1(jtrca);
extern F1(jtrdot1);
extern F1(jtrecip);
extern F1(jtrect);
extern F1(jtretcommq);
extern F1(jtretcomms);
extern F1(jtreverse);
extern F1(jtright1);
extern F1(jtrinv);
extern F1(jtrngraw);
extern F1(jtrngseedq);
extern F1(jtrngseeds);
extern F1(jtrngselectq);
extern F1(jtrngselects);
extern F1(jtrngstateq);
extern F1(jtrngstates);
extern F1(jtroll);
extern F1(jtrollx);
extern F1(jtsb1);
extern F1(jtsborder);
extern F1(jtscind);
extern F1(jtscriptstring);
extern F1(jtscriptnum);
extern F1(jtsclass);
extern F1(jtscm00);
extern F1(jtscm01);
extern F1(jtscm10);
extern F1(jtscm11);
extern F1(jtscnl);
extern F1(jtsct1);
extern F1(jtscz1);
extern F1(jtseclevq);
extern F1(jtseclevs);
extern F1(jtself1);
extern F1(jtshape);
extern F1(jtshapex);
extern F1(jtshasum1);
extern F1(jtshift1);
extern F1(jtsignum);
extern F1(jtsiinfo);
extern F1(jtslash);
extern F1(jtsldot);
extern F1(jtsmmblks);
extern F1(jtsnl);
extern F1(jtsp);
extern F1(jtsparse1);
extern F1(jtspcount);
extern F1(jtspfor);
extern F1(jtspforloc);
extern F1(jtspit);
extern F1(jtsqroot);
extern F1(jtsquare);
extern F1(jtstr0);
extern F1(jtstype);
extern F1(jtswap);
extern F1(jtsymbrd);
extern F1(jtsymbrdlock);
extern F1(jtsymbrdlocknovalerr);
extern F1(jtsympool);
extern F1(jtsysparmq);
extern F1(jtsysparms);
extern F1(jtsysq);
extern F1(jttable);
extern F1(jttail);
extern F1(jttally);
extern F1(jttco);
extern F1(jttdot);
extern F1(jtthorn1);
extern F1(jtthorn1u);
extern F1(jttlimq);
extern F1(jttlims);
extern F1(jttocesu8);
extern F1(jttomutf8);
extern F1(jttou32);
extern F1(jttoutf16);
extern F1(jttoutf16x);
extern F1(jttoutf32);
extern F1(jttoutf8);
extern F1(jttoutf8a);
extern F1(jttoutf8x);
extern F1(jttparse);
extern F1(jttrep);
extern F1(jttrx);
extern F1(jtts);
extern F1(jtts0);
extern F1(jttsit1);
extern F1(jttss);
extern F1(jtuco1);
extern F1(jtunbin);
extern F1(jtunicodex78q);
extern F1(jtunicodex78s);
extern F1(jtunlock1);
extern F1(jtunname);
extern F1(jtunparse);
extern F1(jtunzero);
extern F1(jtvaspz);
extern F1(jtversq);
extern F1(jtvi);
extern F1(jtvib);
extern F1(jtvip);
extern F1(jtvs);
extern F1(jtvslit);
extern F1(jtvtrans);
extern F1(jtwordil);
extern F1(jtwords);
extern F1(jtxco1);
extern F1(jtxepq);
extern F1(jtxeps);

// extern F1(jttest1);

extern F2(jtabase2);
extern F2(jtadot2);
extern F2(jtadverse);
extern F2(jtaes2);
extern F2(jtaflag2);
extern F2(jtagenda);
extern F2(jtagendai);
extern F2(jtamp);
extern F2(jtampco);
extern F2(jtanyebar);
extern F2(jtapplystr);
extern F2(jtatco);
extern F2(jtatop);
extern F2(jtbase2);
extern F2(jtbinrep2);
extern F2(jtbit);
extern F2(jtbit2);
extern F2(jtbitmatch);
extern F2(jtbitwiserotate);
extern F2(jtbitwiseshift);
extern F2(jtbitwiseshifta);
extern F2(jtcant2);
extern F2(jtcd);
extern F2(jtcdot2);
extern F2(jtcdproc2);
extern F2(jtcolon);
extern DF2(jtcork2);
extern F2(jtcpufeature2);
extern F2(jtcrc2);
extern DF2(jtcut2);
extern F2(jtcut);
extern F2(jtdbrr2);
extern F2(jtdbsig2);
extern F2(jtdbstepinto2);
extern F2(jtdbstepout2);
extern F2(jtdbstepover2);
extern F2(jtdeal);
extern F2(jtdealx);
extern F2(jtdgrade2);
extern F2(jtdomainerr2);
extern F2(jtdot);
extern F2(jtdrop);
extern F2(jtebar);
extern F2(jteps);
extern F2(jtetoiso8601);
extern F2(jtiso8601toe);
extern F2(jteven);
extern F2(jtevger);
extern F2(jtexec2);
extern F2(jtexpand);
extern DF2(jtexpn2);
extern F2(jtfc2);
extern F2(jtfetch);
extern F2(jtfit);
extern F2(jtfixrecursive);
extern F2(jtfmt02);
extern F2(jtfmt12);
extern F2(jtfmt22);
extern DF2(jtfold);
extern DF2(jtfoldZ);
extern F2(jtforeign);
extern F2(jtforeignextra);
extern F2(jtfrom);
extern F2(jtfrombs);
extern F2(jtfromis);
extern F2(jtfromr);
extern F2(jtfromsd);
extern F2(jtfromss);
extern F2(jtfsm);
extern F2(jtgemmtune2);
extern F2(jtgenbitwiserotate);
extern F2(jtgenbitwiseshift);
extern F2(jtgenbitwiseshifta);
extern F2(jtgrade1p);
extern F2(jtgrade2);
extern F2(jthexrep2);
extern F2(jthgeom);
extern F2(jthook);
extern F2(jti1ebar);
extern F2(jtic2);
extern F2(jticap2);
extern F2(jtifbebar);
extern F2(jtifrom);
extern F2(jtindexof);
extern F2(jtintdiv);
extern F2(jtjdot2);
extern F2(jtjfappend);
extern F2(jtjfatt2);
extern F2(jtjfperm2);
extern F2(jtjfwrite);
extern F2(jtjico2);
extern F2(jtjiwrite);
extern F2(jtjregmatch);
extern F2(jtjregmatches);
extern F2(jtlamin2);
extern F2(jtlcapco);
extern F2(jtleft2);
extern F2(jtless);
extern F2(jtlink);
extern F2(jtloccre2);
extern F2(jtlock2);
extern F2(jtlocnl2);
extern F2(jtlocpath2);
extern F2(jtlogar2);
extern F2(jtmatch);
extern F2(jtmdiv);
extern F2(jtmemu2);
extern F2(jtmemw);
extern F2(jtnamerefop);
extern F2(jtnl2);
extern F2(jtnotmatch);
extern F2(jtnouninfo2);
extern F2(jtobverse);
extern F2(jtodd);
extern F2(jtordstat);
extern F2(jtordstati);
extern F2(jtoutstr);
extern F2(jtover);
extern F2(jtpco2);
extern F2(jtpderiv2);
extern F2(jtpdt);
extern F2(jtpdtsp);
extern F2(jtpmarea2);
extern F2(jtpoly2);
extern F2(jtqco2);
extern F2(jtqhash12);
extern F2(jtqq);
extern F2(jtrdot2);
extern F2(jtreaxis);
extern F2(jtreitem);
extern F2(jtrepeat);
extern F2(jtrepeatr);
extern F2(jtreshape);
extern DF2(jtresidue);
extern F2(jtrezero);
extern F2(jtright2);
extern F2(jtroot);
extern F2(jtrotate);
extern F2(jtsb2);
extern F2(jtscapco);
extern F2(jtscm002);
extern F2(jtscm012);
extern F2(jtscm102);
extern F2(jtscm112);
extern F2(jtsct2);
extern F2(jtscz2);
extern F2(jtself2);
extern F2(jtsetfv);
extern F2(jtsfrom);
extern F2(jtshasum2);
extern F2(jtsmmcar);
extern F2(jtsmmis);
extern F2(jtsparse2);
extern DF2(jtspecialatoprestart);
extern F2(jtstitch);
extern F2(jtstitchsp2);
extern F2(jtsumebar);
extern F2(jttake);
extern F2(jttcap);
extern F2(jtthorn2);
extern F2(jttie);
extern F2(jttsit2);
extern F2(jtuco2);
extern F2(jtundco);
extern F2(jtunder);
extern F2(jtunlock2);
extern F2(jtunparsem);
extern DF2(jtupon2);
extern F2(jtxco2);
extern DF2(jtxdefn);
extern F2(jtxlog2a);
extern F2(jtxroota);
extern F2(jtxrx);

extern F1(jtamend);
extern DF1(jtbitwise1);
extern DF1(jtbitwiseinsertchar);
extern DF1(jtcrcfixedleft);
extern DF1(jtdetxm);
// obsolete extern DF1(jtdf1);
extern DF1(jtdfs1);
extern DF1(jtexppi);
extern DF1(jtfsmfx);
extern DF1(jthgcoeff);
extern DF1(jtmean);
extern DF1(jtnum1);
extern DF1(jtrazecut1);
extern DF1(jtredcat);
extern DF1(jtredravel);
extern DF1(jtwd);

extern F2(jtapip);
extern DF1(jtatomic1);
extern DF2(jtatomic2);
extern DF2(jtbitwisechar);
extern DF2(jtcharfn2);
extern DF2(jtunquote);
extern DF2(jtdbunquote);
// obsolete extern DF2(jtdf2);
extern DF2(jtdfs2);
extern DF2(jteachl);
extern DF2(jteachr);
extern DF2(jtfslashatg);
extern DF2(jtimplocref);
extern DF2(jtnum2);
extern DF2(jtpolymult);
extern DF2(jtpowop);
extern DF2(jtrazecut0);
extern DF2(jtrazecut2);
extern DF2(jtrollk);
extern DF2(jtrollkx);
extern DF2(jtsumattymes1);
extern DF2(jtxop2);
#if AUDITEXECRESULTS
extern void auditblock(A w, I nonrecurok, I virtok);
#endif
#if FORCEVIRTUALINPUTS
extern A virtifnonip(J jt, I ipok, A buf);
#endif
extern A        jtassembleresults(J,I, A, A,A*,I,I,I,A,I,I,I);
extern void     audittstack(J);
extern I        cachedmmult(J,D*,D*,D*,I,I,I,I);
extern A        jtac1(J,AF);
extern A        jtac2(J,AF);
extern B        jtadd2(J,F,F,C*);
extern I        jtaii(J,A);
extern B        jtaindex(J,A,A,I,A*);
extern A        jtam1a(J,A,A,A,B);
extern A        jtam1e(J,A,A,A,B);
extern A        jtam1sp(J,A,A,A,B);
extern A        jtamna(J,A,A,A,B);
extern A        jtamne(J,A,A,A,B);
extern A        jtamnsp(J,A,A,A,B);
extern A        jtapv(J,I,I,I);
extern A        jtapvwr(J,I,I,I);
extern A        jtascan(J,C,A);
extern A        jtaslash(J,C,A);
extern A        jtaslash1(J,C,A);
extern A        jtatab(J,C,A,A);
extern AF       jtatcompf(J,A,A,A);
extern void     jtauditmemchains(J);
extern B        jtb0(J,A);
extern A        jtbcvt(J,C,A);
extern B*       jtbfi(J,I,A,B);
extern D        jtbindd(J,D,D);
extern B        jtbitwisecharamp(J,UC*,I,UC*,UC*);
extern B        jtboxatop(J,A);
extern A        jtbrep(J,B,B,A);
extern A        jtcelloffset(J,AD * RESTRICT,AD * RESTRICT);
extern A        jtcharmap(J,A,A,A);
extern B        jtcheckmf(J);
extern B        jtchecksi(J);
extern A        jtclonelocalsyms(J,A);
extern A        jtclonevirtual(J,A);
extern I        jtcompare(J,A,A);
extern A        jtconnum(J,I,C*);
extern I        jtcountnl(J);
extern A        jtcpa(J,B,A);
extern A        jtcreatecycliciterator(J,A,A);
extern A        jtcrelocalsyms(J,A,A,I,I,I);
extern A        jtcstr(J,C*);
extern A        jtcvt(J,I,A);
extern B        jtccvt(J,I,A,A*);
extern A        jtcvz(J,I,A);
extern A        jtdaxis(J,I,A);
extern DC       jtdeba(J,C,void*,void*,A);
extern void     jtdebdisp(J,DC);
extern void     jtdebz(J);
extern A        jtdecorate(J,A,I);
extern A        jtdfss1(J,A,A,A);
extern A        jtdfss2(J,A,A,A,A);
extern D        jtdgamma(J,D);
extern D        jtdgcd(J,D,D);
extern D        jtdlcm(J,D,D);
extern A        jtdropr(J,I,A);
extern B        jtecvt(J,D,I,int*,int*,C*);
extern B        jtecvtinit(J);
extern A        jtenqueue(J,A,A,I);
extern B        jtequ(J,A,A);
extern B        jtequ0(J,A,A);
extern A        jtev1(J,A,C*);
extern A        jtev2(J,A,A,C*);
extern A        jteva(J,A,C*);
extern A        jteval(J,C*);
extern A        jtevc(J,A,A,C*);
extern A        jtevery(J,A,A,AF);
extern A        jtevery2(J,A,A,A,AF);
extern A        jtext(J,B,A);
extern A        jtexta(J,I,I,I,I);
extern A*       jtextnvr(J);
extern I        jtfa(J,AD * RESTRICT,I);
extern A        jtfdef(J,I,C,I,AF,AF,A,A,A,I,I,I,I);
#if !USECSTACK
extern I        jtfdep(J,A);
#endif
extern void     jtfh(J,A);
extern void     jtfillv(J,I,I,C*);        /* "fill" name conflict on Mac             */
extern A        jtfindnl(J,I);
extern I        jtfnum(J,A);
extern A        jtfolk(J,A,A,A);  /* "fork" name conflict under UNIX         */
extern A        jtfrombsn(J,A,A,I);
extern A        jtfrombu(J,A,A,I);
extern A        jtfxeachv(J,I,A);
extern RESTRICTF A jtga(J,I,I,I,I*);
extern RESTRICTF A jtgaf(J,I);
extern RESTRICTF A jtgafv(J,I);
extern A        jtgadv(J,A,C);
extern RESTRICTF A jtgah(J,I,A);
extern A        jtgc(J,A,A*);
extern I        jtgc3(J,A*,A*,A*,A*);
extern A        jtgconj(J,A,A,C);
extern B        jtgerexact(J, A);
extern B        jtglobinit(J);
extern B        jthasimploc(J,A);
extern I        jti0(J,A);
extern A        jtifb(J,I,B* RESTRICT);
extern I        jtigcd(J,I,I);
extern I        jtilcm(J,I,I);
extern A        jtincorp(J,A);
extern A        jtindexnl(J,I);
extern A        jtindexofprehashed(J,A,A,A);
extern A        jtindexofss(J,I,A,A);
extern A        jtindexofsub(J,I,A,A);
extern A        jtindexofxx(J,I,A,A);
extern A        jtinpl(J,B,I,C*);
extern A        jtiocol(J,I,A,A);
extern A        jtiovsd(J,I,A,A);
extern A        jtiovxs(J,I,A,A);
extern D        jtintpow(J,D,I);
extern A        jtirs1(J,A,A,I,AF);
extern A        jtirs2(J,A,A,A,I,I,AF);
extern A        jtjerrno(J);
extern A        jtjgets(J,C*);
extern C        jtjinit2(J,int,C**);
extern A        jtinv(J,A,I);  // second arg is forced to 0 for initial call
extern F        jtjope(J,A,C*);
extern L*       jtjset(J,C*,A);
extern void     jtjsigd(J,C*);
extern void     jtjsignal(J,I);
extern void     jtjsignal3(J,I,A,I);
extern A        jtleakblockread(J,A);
extern A        jtleakblockreset(J,A);
extern B        jtlocdestroy(J,A);
extern I        jtmaxtype(J,I,I);
extern B        jtmeminit(J);
extern void     jtmf(J, A);
extern I        jtmult(J,I,I);
extern A        jtnamerefacv(J, A, L*);
extern A        jtnfs(J,I,C*);
extern I        jtnotonupperstack(J,A);
extern A        jtodom(J,I,I,I* RESTRICT);
extern A        jtparsea(J,A*,I);
extern B        jtparseinit(J);
extern A        jtparsex(J,A*,I,CW*,DC);
extern A        jtpaxis(J,I,A);
extern A        jtpcvt(J,I,A);
extern A        jtpee(J,A*,CW*,I,I,DC);
extern A        jtpfill(J,I,A);
extern A        jtpind(J,I,A);
extern B        jtpinit(J);
extern I        jtpiplocalerr(J, A);
extern void     jtpmrecord(J,A,A,I,int);
extern D        jtpospow(J,D,D);
extern B        jtpreparse(J,A,A*,A*);
extern B        jtprimitive(J,A);
extern L*       jtprobe(J,I,C*,UI4,A);
extern L*       jtprobedel(J,I,C*,UI4,A);
extern L*       jtprobeis(J, A, A);
extern L*       jtprobeislocal(J,A);
extern L*       jtprobeisquiet(J, A);
extern L*       jtprobelocal(J,A);
extern I        jtprod(J, I, I*);
extern I        jtqcompare(J,Q,Q);
extern I        jtra(J,AD* RESTRICT,I);
extern A        jtras(J,AD* RESTRICT);
extern A        jtrank1ex(J,AD * RESTRICT,A,I,AF);
extern A        jtrank1ex0(J,AD * RESTRICT,A,AF);
extern A        jtrank2ex(J,AD * RESTRICT,AD * RESTRICT,A,I,I,I,I,AF);
extern A        jtrank2ex0(J,AD * RESTRICT,AD * RESTRICT,A,AF);
extern A        jtrd(J,F,I,I);
extern A        jtrealize(J,A);
extern A        jtredcatcell(J,A,I);
extern D        jtremdd(J,D,D);
extern I        jtremid(J,I,D);
extern A        jtrifvs(J,AD* RESTRICT);
extern B        jtredef(J,A,L*);
extern B        jtrnginit(J);
extern B        jtsbtypeinit(J);
extern A        jtsc(J,I);
extern A        jtsc4(J,I,I);
extern A        jtscansp(J,A,A,AF);
extern A        jtscb(J,B);
extern A        jtscc(J,C);
extern A        jtscf(J,D);
extern B        jtscheck(J,A);
extern A        jtscx(J,X);
extern A        jtscib(J,I);
extern B        jtsesminit(J);
extern void     jtsetleakcode(J,I);
extern A        jtsfn(J,B,A);
extern A        jtsfne(J,A);
extern void     jtshowerr(J);
extern A        jtsparseit(J,A,A,A);
extern I        jtspbytesinuse(J);
extern I        jtspstarttracking(J);
extern void     jtspendtracking(J);
extern B        jtspc(J);
extern A        jtspella(J,A);
extern A        jtspellcon(J,I);
extern A        jtspellout(J,C);
extern B        jtspfree(J);
extern B        jtspmult(J,A*,A,A,C,I,I,I,I);
extern A        jtsprank1(J,A,A,I,AF);
extern A        jtsprank2(J,A,A,A,I,I,AF);
extern A        jtssingleton(J,A,A,A,RANK2T,RANK2T);
extern A        jtssingleton1(J,A,A);
extern A        jtstcreate(J,C,I,I,C*);
extern F        jtstdf(J,A);
extern A        jtstfind(J,I,C*,I);
extern A        jtstfindcre(J,I,C*,I);
extern A        jtstr(J,I,C*);
extern I        jtsumattymesprods(J,I,void *,void *,I,I,I,I,I,void *);
extern B        jtsymbinit(J);
extern L*       jtsymbis(J,A,A,A);
extern L*       jtsymbisdel(J,A,A,A);
extern B        jtsymext(J,B);
extern void     jtsymfreeha(J,A);
extern L*       jtsymnew(J,LX*,LX);
extern A        jtsybaseloc(J,A);
extern L*       jtsyrd(J,A);
extern L*       jtsyrd1(J,I,C*,UI4,A);
extern A        jtsyrdforlocale(J,A);
extern A        jtsyrd1forlocale(J,I,C*,UI4,A);
extern L*       jtsyrdfromloc(J,A,A);
extern L*       jtsyrdnobuckets(J,A);
extern A        jttaker(J,I,A);
extern D        jttceil(J,D);
extern D        jttfloor(J,D);
extern I        jtthv(J,A,I,C*);
extern A        jttoc1(J,B,A);
extern void     jttoutf8w(J,C*,I,US*);
extern void       jttpop(J,A*);
extern A*       jttpush(J,AD* RESTRICT,I,A*);
extern B        jttrd(J jt,A w);
extern A*       jttg(J,A*);
extern A        jttokens(J,A,I);
extern B        jtunlk(J,I);
extern A        jtv2(J,I,I);
extern A        jtva2s(J,A,A,C,VF,I,I,I,I,I);
// obsolate extern C        jtvaid(J,A);
extern VARPS      jtvains(J,A,I);
extern VARPS      jtvapfx(J,A,I);
extern VA2      jtvar(J,A,I,I);
extern VARPS      jtvasfx(J,A,I);
extern A        jtvasp(J,A,A,C,VF,I,I,I,I,I,I,I,I,I);
extern B        jtvc1(J,I,US*);
extern A        jtvci(J,I);
extern A        jtvec(J,I,I,void*);
extern A        jtvecb01(J,I,I,void*);
extern F        jtvfn(J,F);
extern A        jtvger2(J,C,A,A);
extern A        jtvirtual(J,AD * RESTRICT,I,I);
extern B        jtvnm(J,I,C*);
extern void     jtwri(J,I,C*,I,C*);
extern A        jtxcvt(J,I,A);
extern B        jtxlinit(J);
extern B        jtxoinit(J);
extern B        jtxsinit(J);

extern B        all0(A);
extern B        all1(A);
extern I        allosize(A);
extern I        atoplr(A);
extern I        atype(I);
extern I        boxat(A,I,I,I);
extern I        bsum(I,B*);
extern C        cf(A);
extern C        cl(A);
extern CR       condrange(I *,I,I,I,I);
extern CR       condrange2(US *,I,I,I,I);
extern CR       condrange4(C4 *,I,I,I,I);
extern B        evoke(A);
extern void     forcetomemory(void *);
extern UI       hic(I,UC*);
extern UI       hic2(I,UC*);
extern UI       hic4(I,UC*);
extern I        hsize(I);
extern J        jinit(void);
extern void     jsto(J,I,C*);
extern void     jstpoll(J);
extern void     jststop(J);
extern I        level(A);
extern I        levelle(A,I);
extern void     mvc(I,void*,I,void*);
extern B        nameless(A);
extern D        qpf(void);
extern A        relocate(I,A);
extern I        remii(I,I);
extern C        spellin(I,C*);
extern void     spellit(C,C*);
extern I        smmallosize(A);
extern void     smmfrr(A);
extern void     sortiq1(I*,I);
extern I        strtoI10s(I,C*);
extern D        tod(void);
extern void     va1primsetup(A);
extern void     va2primsetup(A);
extern B        vlocnm(I,C*);
extern D        xdouble(X);


struct Bd1 {I hdr[AKXR(0)/SZI]; D v[1];};
struct Bd2;
extern struct Bd2 Ba0j1;
#define a0j1 ((A)&Ba0j1)
// obsolete extern A        ds(CACE);
// obsolete extern A        ainf;
extern struct Bd1 Bainf;
#define ainf ((A)&Bainf)
// obsolete extern A        ds(CALP);
// obsolete extern A        aqq;
// obsolete extern A        mtv;
// obsolete extern A        mtm;
extern I Baqq[];
#define aqq ((A)&Baqq)
extern I Bmtv[];
#define mtv ((A)&Bmtv)
extern I Bmtm[];
#define mtm ((A)&Bmtm)
// obsolete extern A        asgnlocsimp;  // points to block with ASGN+ASGNLOCAL+ASGTONNAME
// obsolete extern A        asgngloname;  // points to block with ASGN+ASGNTONAME
// obsolete extern A        asgnforceglo;  // points to block with ASGN but char is =. CASGN
// obsolete extern A        asgnforcegloname;  // points to block with ASGN+ASGNTONAME  but char is =. CASGN
// obsolete extern const UC       bit[];
// obsolete extern A        imax;
// obsolete extern A        mark;
extern I Basgnlocsimp[];
#define asgnlocsimp ((A)&Basgnlocsimp)
extern I Basgngloname[];
#define asgngloname ((A)&Basgngloname)
extern I Basgnforceglo[];
#define asgnforceglo ((A)&Basgnforceglo)
extern I Basgnforcegloname[];
#define asgnforcegloname ((A)&Basgnforcegloname)
extern I Bimax[];
#define imax ((A)&Bimax)
extern I Bmark[];
#define mark ((A)&Bmark)
extern C        breakdata;
// obsolete extern A        chr[];
extern I Bchrcolon[];
#define chrcolon ((A)&Bchrcolon)
extern I Bchrspace[];
#define chrspace ((A)&Bchrspace)
extern C  ctype[];
extern const double dzero;
extern D        inf;
extern D        infm;
// obsolete extern A        iv0;
// obsolete extern A        iv1;
extern I Biv0[];
#define iv0 ((A)&Biv0)
extern I Biv1[];
#define iv1 ((A)&Biv1)
extern D        jnan;           /* "nan" name conflict under Solaris       */
// obsolete extern I        liln;
// obsolete extern C        minus0[];
extern A        mnuvxynam[6];
extern void     moveparseinfotosi(J);
// obsolete extern A        numv[];
extern I Bnum[][9-SY_64];
#define zeroionei(n) ((A)(Bnum+(n)))
#define num(n) ((A)(Bnum+2+(n)-NUMMIN))
// obsolete extern A        numvr[3];
extern struct Bd1 Bnumvr[];
#define numvr(n) ((A)(Bnumvr+(n)))
// obsolete extern A        onehalf;
extern struct Bd1 Bonehalf;
#define onehalf ((A)&Bonehalf)
extern D        pf;
// obsolete extern A        pie;            /* "pi" name conflict                      */
extern struct Bd1 Bpie;
#define pie ((A)&Bpie)
// obsolete extern A        pst[];
extern PRIM     primtab[];
extern const UI4      shortrange[3][4];
// obsolete extern A        zeroionei[2];
extern Z        zeroZ;
extern const dcomplex zone;
extern const dcomplex zzero;
extern A        zpath;
/* cpu feature */
extern UC       hwaes;
extern UC       hwfma;
#if (SYS & SYS_ATARIST+SYS_ATT3B1)
extern int      memcmp();       /* C library fn                            */
extern D        strtod();       /* C library fn                            */
extern I        strtol();       /* C library fn                            */
#endif
