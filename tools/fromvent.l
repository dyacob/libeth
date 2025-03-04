%{
#include <stdio.h>
int caption=0, head3=0, bullet=0, numbullet=0, poem=0, head1=0, head2=0, author=0, row=0, underline=0;
%}

%s F129 F130 F131 F132 ENGLISH

%%

"<F130"D?[0-9]*%?-?[0-9]*">"|"<F255"(P)?[0-9]+?(M|D)?">"     { BEGIN F130; }
"<F130P255D>"      { BEGIN F130; }
"<F131"(M|D)?">"   { BEGIN F131; }
"<F132"(D)?">"     { BEGIN F132; }
"<F132P255D>"      { BEGIN F132; }
"<F129"(P)?[0-9]*(M)?">"	{ BEGIN F129; /* These Are Icons */ }
"<F2P12B>"			{ BEGIN ENGLISH; }


"@Body Text = "				{ }
"@CAPTION-10 = @@   @   @"	{ printf ("<hr>"); }
"@CAPTION-10 = "			{ printf ("<p align=\"center\">"); }
"@TXT"(-[A-Z]+)?(-[0-9]+)?" = "	{ printf ("<p>"); }
"@CONTNT-CNTR16 = " |
"@HEAD-CNTR"(24|27|30)" = "		{ printf ("<h1 align=\"center\"><sera>"); head1 = 1;}
@(CONTNT|HEAD)-CNTR(18|20)" = " { printf ("<h2 align=\"center\"><sera>"); head2 = 1;}
"@HEAD-CNTR1"[246]" = "         { printf ("<h3 align=\"center\"><sera>"); head3 = 1;}
"@BUL-10 = "				{ if ( !bullet ) {
                                printf ("<ul>\n");
                                bullet=1;
							  }
                              printf ("  <li>");
							}
"@NO-OUTDNT"[0-9]*-[0-9]+" = "			{ if ( !numbullet ) {
                                printf ("<ul>\n");
                                numbullet=1;
							  }
							}
"@POEM-"(LFT|IND)[0-9]+" = "			{ if ( !poem ) {
                                printf ("\n<blockquote><i>\n");
                                poem=1;
							  }
							}
"@TXT-TIG-L&R = "			{ printf ("<p align=\"center\"><b>"); author=1; }
"@TXT-TIG10-2 = \n\n"|"@TXT-TIG10-2 = "		{ }
"@LEVEL1-16 = "				{ }
"@LEVEL1-14 = "|"@TAB-"[A-Z0-9]+" = "|"@TAB"[0-9]+--[0-9]+	{ printf ("\n<table>\n  <tr><td><sera>");  row=1;}      
						  

<F129>.		{ }
<F130>"\""	{ printf ("he"); }
<F130>#		{ printf ("hu"); }
<F131>A		{ printf ("hi"); }
<F130>"$"		{ printf ("ha"); }
<F130>%		{ printf ("hE"); }
<F130>&		{ printf ("h"); }
<F130>"/"	{ printf ("ho"); }
	
<F130>=		{ printf ("le"); }
<F130>A		{ printf ("lu"); }
<F130>B		{ printf ("li"); }
<F130>C		{ printf ("la"); }
<F130>D		{ printf ("lE"); }
<F130>E		{ printf ("l"); }
<F130>F		{ printf ("lo"); }
<F131>">"|"<62>"		{ printf ("lWa"); }
	
<F130>G		{ printf ("He"); }
<F131>B		{ printf ("Hu"); }
<F131>C		{ printf ("Hi"); }
<F131>D		{ printf ("Ha"); }
<F131>E		{ printf ("HE"); }
<F130>H		{ printf ("H"); }
<F131>F		{ printf ("Ho"); }
	
<F130>I		{ printf ("me"); }
<F130>J		{ printf ("mu"); }
<F130>K		{ printf ("mi"); }
<F130>L		{ printf ("ma"); }
<F130>M		{ printf ("mE"); }
<F130>N		{ printf ("m"); }
<F130>O		{ printf ("mo"); }
<F131>"("	{ printf ("mWa"); }
	
<F131>G		{ printf ("`se"); }
<F131>H		{ printf ("`su"); }
<F131>I		{ printf ("`si"); }
<F131>J		{ printf ("`sa"); }
<F131>K		{ printf ("`sE"); }
<F130>P		{ printf ("`s"); }
<F131>L		{ printf ("`so"); }
	
<F130>Q		{ printf ("re"); }
<F130>R		{ printf ("ru"); }
<F130>S		{ printf ("ri"); }
<F130>T		{ printf ("ra"); }
<F130>U		{ printf ("rE"); }
<F130>V		{ printf ("r"); }
<F130>W		{ printf ("ro"); }
<F131>"?"	{ printf ("rWa"); }
	
<F130>X		{ printf ("se"); }
<F130>Y		{ printf ("su"); }
<F130>Z		{ printf ("si"); }
<F130>"["	{ printf ("sa"); }
<F130>"]"	{ printf ("sE"); }
<F130>"^"	{ printf ("s"); }
<F130>a		{ printf ("so"); }
<F131>"<180>"		{ printf ("sWa"); }
	
<F130>b				{ printf ("xe"); }
<F131>M				{ printf ("xu"); }
<F131>N				{ printf ("xi"); }
<F131>O				{ printf ("xa"); }
<F131>P				{ printf ("xE"); }
<F130>c				{ printf ("x"); }
<F130>d|"<100>"		{ printf ("xo"); }
<F131>"<181>"		{ printf ("xWa"); }
	
<F130>e|"<101>"		{ printf ("qe"); }
<F130>f|"<102>"		{ printf ("qu"); }
<F131>Q				{ printf ("qi"); }
<F130>g|"<103>"		{ printf ("qa"); }
<F131>R				{ printf ("qE"); }
<F130>h|"<104>"		{ printf ("q"); }
<F130>i|"<105>"		{ printf ("qo"); }
<F131>"<177>"		{ printf ("qWa"); }
	
<F131>"<189>"		{ printf ("Qe"); }
<F131>"<190>"		{ printf ("Qu"); }
<F131>"<191>"		{ printf ("Qi"); }
<F131>"<192>"		{ printf ("Qa"); }
<F132>%				{ printf ("QE"); }
<F131>"<193>"		{ printf ("Q"); }
<F131>"<194>"		{ printf ("Qo"); }
	
<F130>j|"<106>"		{ printf ("be"); }
<F130>k|"<107>"		{ printf ("bu"); }
<F130>l|"<108>"		{ printf ("bi"); }
<F130>m|"<109>"		{ printf ("ba"); }
<F130>o|"<111>"		{ printf ("bE"); }
<F130>p|"<112>"		{ printf ("b"); }
<F130>q|"<113>"		{ printf ("bo"); }
<F132>"*"			{ printf ("bWa"); }
	
<F131>"<136>"		{ printf ("ve"); }
<F131>"<142>"		{ printf ("vu"); }
<F131>"<151>"		{ printf ("vi"); }
<F131>"<158>"		{ printf ("va"); }
<F131>"<167>"		{ printf ("vE"); }
<F131>"\""			{ printf ("v"); }
<F131>"$"			{ printf ("vo"); }
	
<F130>r|"<114>"		{ printf ("te"); }
<F130>s|"<115>"		{ printf ("tu"); }
<F130>t|"<116>"		{ printf ("ti"); }
<F130>u|"<117>"		{ printf ("ta"); }
<F130>v|"<118>"		{ printf ("tE"); }
<F130>w|"<119>"		{ printf ("t"); }
<F130>x|"<120>"		{ printf ("to"); }
<F131>"<187>"		{ printf ("tWa"); }
	
<F130>y|"<121>"		{ printf ("ce"); }
<F130>z|"<122>"		{ printf ("cu"); }
<F131>S				{ printf ("ci"); }
<F131>T				{ printf ("ca"); }
<F131>U				{ printf ("cE"); }
<F130>"{"|"<123>"		{ printf ("c"); }
<F131>V				{ printf ("co"); }
<F132>"$"			{ printf ("cWa"); }
	
<F131>W				{ printf ("`he"); }
<F131>X				{ printf ("`hu"); }
<F131>Y				{ printf ("`hi"); }
<F131>Z				{ printf ("`ha"); }
<F131>"^"			{ printf ("`hE"); }
<F131>a				{ printf ("`h"); }
<F131>b				{ printf ("`ho"); }
<F130>"<209>"		{ printf ("hWa"); }
	
<F130>"|"|"<124>"		{ printf ("ne"); }
<F130>"}"|"<125>"		{ printf ("nu"); }
<F130>"<128>"		{ printf ("ni"); }
<F130>"<129>"		{ printf ("na"); }
<F130>"<130>"		{ printf ("nE"); }
<F130>"<131>"		{ printf ("n"); }
<F130>"<132>"		{ printf ("no"); }
<F132>&				{ printf ("nWa"); }
	
<F131>c				{ printf ("Ne"); }
<F131>d|"<100>"		{ printf ("Nu"); }
<F131>e|"<101>"		{ printf ("Ni"); }
<F130>"<133>"		{ printf ("Na"); }
<F131>f|"<102>"		{ printf ("NE"); }
<F131>g|"<103>"		{ printf ("N"); }
<F131>h|"<104>"		{ printf ("No"); }
<F132>'				{ printf ("NWa"); }
	
<F130>" <134>"		{ printf (" a"); }
<F130>" <135>"		{ printf (" u"); }
<F130>" <136>"		{ printf (" i"); }
<F130>" <137>"		{ printf (" a"); }
<F130>" <138>"		{ printf (" E"); }
<F130>" <139>"		{ printf (" I"); }
<F130>" <140>"		{ printf (" o"); }
<F130>"<134>"		{ printf ("'a"); }
<F130>"<135>"		{ printf ("'u"); }
<F130>"<136>"		{ printf ("'i"); }
<F130>"<137>"		{ printf ("'a"); }
<F130>"<138>"		{ printf ("'E"); }
<F130>"<139>"		{ printf ("'I"); }
<F130>"<140>"		{ printf ("'o"); }
	
<F130>"<141>"		{ printf ("ke"); }
<F130>"<142>"		{ printf ("ku"); }
<F130>"<143>"		{ printf ("ki"); }
<F130>"<144>"		{ printf ("ka"); }
<F130>"<145>"		{ printf ("kE"); }
<F130>"<146>"		{ printf ("k"); }
<F130>"<147>"		{ printf ("ko"); }
<F131>"<200>"		{ printf ("kWa"); }
	
<F130>"<148>"		{ printf ("Ke"); }
<F131>i|"<105>"		{ printf ("Ku"); }
<F131>j|"<106>"		{ printf ("Ki"); }
<F131>k|"<107>"		{ printf ("Ka"); }
<F131>l|"<108>"		{ printf ("KE"); }
<F130>"<149>"		{ printf ("K"); }
<F131>m|"<109>"		{ printf ("Ko"); }
<F131>"<204>"		{ printf ("KWa"); }
	
<F130>"<150>"		{ printf ("we"); }
<F130>"<151>"		{ printf ("wu"); }
<F131>o|"<111>"		{ printf ("wi"); }
<F130>"<152>"		{ printf ("wa"); }
<F131>p|"<112>"		{ printf ("wE"); }
<F130>"<153>"		{ printf ("w"); }
<F130>"<154>"		{ printf ("wo"); }
	
<F130>"<155>"		{ printf ("`e"); }
<F131>q|"<113>"		{ printf ("`u"); }
<F131>r|"<114>"		{ printf ("`i"); }
<F130>"<156>"		{ printf ("`a"); }
<F131>s|"<115>"		{ printf ("`E"); }
<F130>"<157>"		{ printf ("`I"); }
<F131>t|"<116>"		{ printf ("`o"); }
	
<F130>"<158>"		{ printf ("ze"); }
<F130>"<159>"		{ printf ("zu"); }
<F130>"<160>"		{ printf ("zi"); }
<F130>"<161>"		{ printf ("za"); }
<F130>"<162>"		{ printf ("zE"); }
<F130>"<163>"		{ printf ("z"); }
<F131>u|"<117>"		{ printf ("zo"); }
<F132>"<<"|"<60>"	{ printf ("zWa"); }
	
<F131>v|"<118>"		{ printf ("Ze"); }
<F131>w|"<119>"		{ printf ("Zu"); }
<F131>x|"<120>"		{ printf ("Zi"); }
<F131>y|"<121>"		{ printf ("Za"); }
<F131>z|"<122>"		{ printf ("ZE"); }
<F131>"{"|"<123>"	{ printf ("Z"); }
<F131>"|"|"<124>"	{ printf ("Zo"); }
<F132>P				{ printf ("ZWa"); }
	
<F130>"<164>"		{ printf ("ye"); }
<F130>"<165>"		{ printf ("yu"); }
<F131>"}""<125>"	{ printf ("yi"); }
<F130>"<166>"		{ printf ("ya"); }
<F130>"<167>"		{ printf ("yE"); }
<F130>"<168>"		{ printf ("y"); }
<F130>"<169>"		{ printf ("yo"); }
	
<F130>"<170>"		{ printf ("de"); }
<F130>"<171>"		{ printf ("du"); }
<F130>"<172>"		{ printf ("di"); }
<F130>"<173>"		{ printf ("da"); }
<F130>"<176>"		{ printf ("dE"); }
<F130>"<177>"		{ printf ("d"); }
<F130>"<178>"		{ printf ("do"); }
<F132>Q				{ printf ("dWa"); }
	
<F130>"<179>"		{ printf ("je"); }
<F131>"<128>"		{ printf ("ju"); }
<F131>"<129>"		{ printf ("ji"); }
<F131>"<130>"		{ printf ("ja"); }
<F130>"<180>"		{ printf ("jE"); }
<F130>"<181>"		{ printf ("j"); }
<F131>"<131>"		{ printf ("jo"); }
<F131>"<212>"		{ printf ("jWa"); }
	
<F130>"<182>"		{ printf ("ge"); }
<F130>"<183>"		{ printf ("gu"); }
<F130>"<184>"		{ printf ("gi"); }
<F130>"<185>"		{ printf ("ga"); }
<F130>"<186>"		{ printf ("gE"); }
<F130>"<187>"		{ printf ("g"); }
<F130>"<189>"		{ printf ("go"); }
<F131>"<210>"		{ printf ("gWa"); }
	
<F130>"<190>"		{ printf ("Te"); }
<F131>"<132>"		{ printf ("Tu"); }
<F131>"<133>"		{ printf ("Ti"); }
<F130>"<191>"		{ printf ("Ta"); }
<F131>"<134>"		{ printf ("TE"); }
<F130>"<192>"		{ printf ("T"); }
<F131>"<135>"		{ printf ("To"); }
<F132>S				{ printf ("TWa"); }
	
<F130>"<193>"		{ printf ("Ce"); }
<F130>"<194>"		{ printf ("Cu"); }
<F131>"<137>"		{ printf ("Ci"); }
<F131>"<138>"		{ printf ("Ca"); }
<F131>"<139>"		{ printf ("CE"); }
<F131>"<140>"		{ printf ("C"); }
<F131>"<141>"		{ printf ("Co"); }
<F132>T				{ printf ("CWa"); }
	
<F131>"<143>"		{ printf ("Pe"); }
<F131>"<144>"		{ printf ("Pu"); }
<F131>"<145>"		{ printf ("Pi"); }
<F131>"<146>"		{ printf ("Pa"); }
<F131>"<147>"		{ printf ("PE"); }
<F131>"<148>"		{ printf ("P"); }
<F131>"<149>"		{ printf ("Po"); }
	
<F130>"<195>"		{ printf ("Se"); }
<F131>"<152>"		{ printf ("Su"); }
<F131>"<153>"		{ printf ("Si"); }
<F131>"<154>"		{ printf ("Sa"); }
<F131>"<155>"		{ printf ("SE"); }
<F130>"<199>"		{ printf ("S"); }
<F131>"<156>"		{ printf ("So"); }
<F132>"]"			{ printf ("SWa"); }
	
<F131>"<159>"		{ printf ("`Se"); }
<F131>"<160>"		{ printf ("`Su"); }
<F131>"<161>"		{ printf ("`Si"); }
<F131>"<162>"		{ printf ("`Sa"); }
<F131>"<163>"		{ printf ("`SE"); }
<F131>"<164>"		{ printf ("`S"); }
<F131>"<165>"		{ printf ("`So"); }
	
<F130>"<200>"		{ printf ("fe"); }
<F130>"<201>"		{ printf ("fu"); }
<F131>"<168>"		{ printf ("fi"); }
<F130>"<202>"		{ printf ("fa"); }
<F130>"<203>"		{ printf ("fE"); }
<F130>"<204>"		{ printf ("f"); }
<F130>"<205>"		{ printf ("fo"); }
<F132>"<122>"		{ printf ("fWa"); }
	
<F130>"<206>"		{ printf ("pe"); }
<F131>"<169>"		{ printf ("pu"); }
<F131>"<170>"		{ printf ("pi"); }
<F131>"<171>"		{ printf ("pa"); }
<F131>"<172>"		{ printf ("pE"); }
<F130>"<207>"		{ printf ("p"); }
<F130>"<208>"		{ printf ("po"); }
	
<F130>1				{ printf ("1"); }
<F130>2				{ printf ("2"); }
<F130>3				{ printf ("3"); }
<F130>4				{ printf ("4"); }
<F130>5				{ printf ("5"); }
<F130>6				{ printf ("6"); }
<F130>7				{ printf ("7"); }
<F130>8				{ printf ("8"); }
<F130>9				{ printf ("9"); }
<F130>10			{ printf ("10"); }
	
<F130>20		 	{ printf ("20"); }
<F130>30			{ printf ("30"); }
<F130>40			{ printf ("40"); }
<F130>50			{ printf ("50"); }
<F130>60			{ printf ("60"); }
<F130>70			{ printf ("70"); }
<F130>80			{ printf ("80"); }
<F130>90			{ printf ("90"); }

<F130>;				{ printf (";"); }
"<F14"(M)?">:"		{ printf (" : "); }
"<F14"(M)?">:-"		{ printf (":-"); }
"<F14"(M)?">%"		{ printf ("%c", 0x25); }
<F130>,				{ printf ("-:"); }
<F130><197>			{ printf ("-"); }
<F130>"*"			{ printf ("::"); }
<F130>"+"			{ printf (","); }
<F130>"("			{ printf ("/"); }
"<D"(%)?-?[0-9]*">"	{ if (underline)
					    {
					      printf ("</u>");
					      underline = 0;
					    }
					}
"<%"-?[0-9]*">"			{ }

" "*"<$B1>"			{  }
"<F130P14>"			{ printf ("<b>"); BEGIN F130; } 
"<F130P"[0-9]*%?-?[0-9]*(M|D)?">" { BEGIN F130; }
"<P255>"			{ printf ("</b>"); } 
"<P13MU>"|"<MU>" 	{ printf ("<u>"); underline=1;} 
"<P255D>"			{ if (underline)
					    {
					      printf ("</u>");
					      underline = 0;
					    }
					}
"<P255"(%)?-?[0-9]*">" { }
"<P13>"				{ }
	
<F130>!				{ printf ("!"); }
<F130>F|"<46>"		{ printf ("@"); }
<F130>"<<"|"<60>"	{ printf ("&laquo;"); }
<F130>">>"|"<62>"	{ printf ("&raquo;"); }
<F130>"?"			{ printf ("?"); }
	
<F131>"<173>"		{ printf ("qWe"); }
<F131>"<178>"		{ printf ("qWE"); }
<F131>"<179>"		{ printf ("qW"); }
	
<F132>">"			{ printf ("hWe"); }
<F132>M				{ printf ("hWi"); }
<F132>N				{ printf ("hWE"); }
<F132>O				{ printf ("hW"); }
	
<F131>"<195>"		{ printf ("kWe"); }
<F131>"<199>"		{ printf ("kWi"); }
<F132>R				{ printf ("kWE"); }
<F131>"<201>"		{ printf ("kW"); }
	
<F131>"<202>"		{ printf ("KWe"); }
<F131>"<203>"		{ printf ("KWi"); }
<F132>"^"			{ printf ("KWE"); }
<F132>`				{ printf ("KW"); }
	
<F131>"<208>"		{ printf ("gWe"); }
<F131>"<209>"		{ printf ("gWi"); }
<F132>p|"<112>"		{ printf ("gWE"); }
<F131>"<211>"		{ printf ("gW"); }

\r					{ }
\n(\r)?\n"@BUL-10 = " { if (bullet) 
					 	 {
						   printf ("\n\n  <li>");   
						 }
						else
					 	 {
						   printf ("\n\n<ul>\n  <li>");   
						   bullet = 1;
						 }
					  }
\n(\r)?\n"@POEM-"(LFT|IND)[0-9]+" = " {
                  		 if(head3)
						   {
						     printf ("</sera></h3>\n\n");
						     head3 = 0;
						   }
                  		 else if(head2)
						   {
						     printf ("</sera></h2>\n\n");
						     head2 = 0;
						   }
                  		 else if(head1)
						   {
						     printf ("</sera></h1>\n\n");
						     head1 = 0;
						   }
						  if (!poem)
					 	   {
						     printf ("\n\n<blockquote><i>\n");   
						     poem = 1;
						   }
						 else
						   printf ("\n");   
					  }
\n(\r)?\n("@LEVEL1-14 = ")|("@TAB-"[A-Z0-9]+" = ")   { 
                      if (row)
						{
						  printf ("</sera></td></tr>\n  <tr><td><sera>");   
						}
                      else
						{
						  printf ("\n<table>\n  <tr><td><sera>");
						  row = 1;
						}
					}
\n(\r)?\n"@TXT"(-[A-Z]+)?(-[0-9]+)?" = " |
\n(\r)?\n 			{
                      if (head1)
						{
						  printf ("</sera></h1>\n\n<p>");
						  head1 = 0;
						}
                      else if (head2)
						{
						  printf ("</sera></h2>\n\n<p>");
						  head2 = 0;
						}
                      else if (head3)
						{
						  printf ("</sera></h3>\n\n<p>");
						  head3 = 0;
						}
					  else if (bullet) 
						{
						  printf ("\n</ul>\n\n<p>");
						  bullet = 0;
						}
					  else if (numbullet) 
						{
						  printf ("\n</ul>\n\n<p>");   
						  numbullet = 0;
						}
					  else if (poem) 
						{
						  printf ("\n</i></blockquote>\n\n");
						  poem = 0;
						}
					  else if (author) 
						{
						  printf ("</b></p>\n\n");   
						  author = 0;
						}
                      else if (row)
						{
						  printf ("</sera></td></tr>\n</table>\n\n");   
						  row = 0;
						}
					  else
						printf ("</p>\n\n<p>");   

                    }

""+				{ }
<ENGLISH>.|\n		{ ECHO; }
.|\n				{ ECHO; }

%%

main ()
{
  printf ( "<html>\n" );
  printf ( "<head>\n  <title></title>\n</head>\n" );
  printf ( "<body bgcolor=\"#f0f0f0\">\n\n" );
  printf ("<sera>\n");
  yylex();
  printf ( "\n\n</sera>\n</body>\n</html>" );
}
