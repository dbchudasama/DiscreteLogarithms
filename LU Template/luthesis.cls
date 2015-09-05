%% Loughborough University Thesis Class
%% based on report.cls
%% Matthew Tylee Atkinson, John Whitley, Mark Withall and Iain Phillips
%%
%%	FIXME Replace cert of authenticity with RSO version.
%%		This is because the RSO one has many errors.
%%		Unfortunately we don't anticipate this will be possible for a while.
%%
%% Installation:
%%		Extract the luthesis ZIP file into ~/texmf/tex/latex/ on *nix
%%			or ~/Library/texmf/tex/latex/ on Mac OS X running MacTeX.
%%		If you want to use the logos elsewhere, you can put them in
%%			another directory, such as ~/texmf/tex/latex/logos/. As
%%			long as they're under ~/texmf/tex/latex/, they should be
%%			automagically found by the *tex compiler.
%%
%% Usage:
%%		* Pass the ``mono'' option to this document class for the hardcopy
%%		  version of your thesis.  It will make all luthesis-included logos
%%		  and forms greyscale and will tell all colours (such as those used
%%		  by hyperref) to be black.  Please note that this won't affect any
%%		  figures you include yourself (but this is probably what you want).
%%      * Don't specify a \date{} -- use the following instead.
%%          + \thesisDateDay{35th}
%%          + \thesisDateMonth{12} -- it will be turned into the name.
%%          + \thesisDateYear{2042}
%%        REASON: Different formats of the date are needed in places.
%%      * For specifying the date of printing for the forms, use the
%%        following commands.
%%          + \thesisSignedDay{-17th}
%%          + \thesisSignedMonth{01} -- it will be turned into the name.
%%          + \thesisSignedYear{2043}
%%        REASON: Print date may differ from content-finalised date.
%%      * The \frontmatter, \mainmatter and \backmatter commands have
%%        been added from book.cls with the rough behaviour of those
%%        from memoir -- i.e. in \frontmatter, chapters are not numbered
%%        but they do appear in the TOC.
%%		  REASON: Use \frontmatter after \maketitle; \mainmatter after the
%%				  ToC, LoF and LoT and \backmatter after the bibliography,
%%				  for the appendices (see next note).
%%      * Appendices should appear *after* the References section (i.e.
%%        they should be the very last thing; slicing all pages from the
%%        the start of the first appendix onwards off the end of your
%%        thesis should not change it logically at all).
%%		  NOTE: Use \appendix before you start your first appendix.
%%
%% Highly-recommended Sister Packages:
%%      * booktabs -- produces tables with the proper rules; makes your
%%        document much more professional-looking; gives advice on table
%%        layout.
%%		* hyperref -- make links in your document for easy navigation.
%%		  NOTE: We pass some more subdued default colours and settings to
%%				hyperref to make reading easier on the eyes.
%%      * glossaries -- useful for both glossaries and acronyms.
%%      * gcite -- formats citations in a much more readable way.  This
%%        ensures that your thesis should be easier to read.
%%
%% Changes from report.cls:
%%      * Added a mono option to remove coloured text and use a black
%%        version of the logo (also removes hyper colours).  NB: Use this
%%		  for the hardcopy version of your thesis!
%%		* 1in margin except on the left, where it's 1.5in.
%%      * A title page to comply with Loughborough content requirements.
%%		  (NB: vertical centering required padding as detailed in
%%		  http://en.wikibooks.org/wiki/LaTeX/Page_Layout [16/04/2008].)
%%      * A thesis access form page (currently from RSO; sorry it's so bad).
%%      * A certificate of originality page.
%%      * A4 paper, 12pt, oneside, 1+1/2 spacing by default. (The Rules.)
%%      * The babel package is loaded with the option ``british'' so
%%        that localisation of things like dates (from biblatex, for
%%        example) is transparently done.
%%		* Section numbering and appearance in ToC now goes down to
%%		  sub-sub-section level.  It is not necessarily recommended you take
%%		  advantage of this -- in fact, try to avoid it!
%%		* Section headings will not be hyphenated (this was considered
%%		  ugly by consensus of the research group of the developers); instead
%%		  they will be \raggedright.  Note that they can still be hyphenated
%%		  in the ToC and that all other text still will be.
%%
%% Options:
%%  mono: obvious
%%  iwp: do page numbering according to sensible rules (use this
%%       if your supervisor is Iain Phillips, or if you're generally a
%%       sensible person.
%%  noaccess: don't include thesis access agreement
%%  nocertorig: don't include certificate of originality
%%  first,second,third, up to sixth: for reports at the end of each year
%%  transfer: for transfer reports
%%     if you use first,...,sixth or transfer, then
%%          noaccess and nocertorig are applied 

\NeedsTeXFormat{LaTeX2e}[1996/06/01]
\ProvidesClass{luthesis}[2012/02/19]
\LoadClass[a4paper,12pt,oneside,onecolumn,final,openany,titlepage]{report}
\RequirePackage[british]{babel}
\RequirePackage[onehalfspacing]{setspace}
\RequirePackage[margin=1in,left=1.5in]{geometry}
\RequirePackage{ifthen,sectsty}  % 'sectsty' for raggedright headings
\allsectionsfont{\raggedright}

%%%
%%% Class Options
%%%
\newboolean{@mono}\setboolean{@mono}{false}
\newboolean{@access}\setboolean{@access}{true}
\newboolean{@certorig}\setboolean{@certorig}{true}
\newboolean{@iwp}\setboolean{@iwp}{false}
\DeclareOption{mono}{%
    \setboolean{@mono}{true}%
    \PassOptionsToPackage{monochrome}{color}%
}
\DeclareOption{nocertorig}{%
    \setboolean{@certorig}{false}%
}
\DeclareOption{noaccess}{%
    \setboolean{@access}{false}%
}
\DeclareOption{iwp}{%
    \setboolean{@iwp}{true}%
}

%% Just because the class supports up to eleventh year reports
%% doesn't mean the Univeristy will accept it ...
\global\let\lt@year\@empty
\DeclareOption{first}{\def\lt@year{First Year}}
\DeclareOption{second}{\def\lt@year{Second Year}}
\DeclareOption{third}{\def\lt@year{Third Year}}
\DeclareOption{fourth}{\def\lt@year{Fourth Year}}
\DeclareOption{fifth}{\def\lt@year{Fifth Year}}
\DeclareOption{sixth}{\def\lt@year{Sixth Year}}
\DeclareOption{seventh}{\def\lt@year{Seventh Year}}
\DeclareOption{eighth}{\def\lt@year{Eighth Year}}
\DeclareOption{ninth}{\def\lt@year{Ninth Year}}
\DeclareOption{tenth}{\def\lt@year{Tenth Year}}
\DeclareOption{eleventh}{\def\lt@year{Eleventh Year}}
\DeclareOption{transfer}{\def\lt@year{Transfer}}

\ProcessOptions

\ifx\lt@year\@empty
\relax
\else
\setboolean{@access}{false}
\setboolean{@certorig}{false}
\fi


\PassOptionsToPackage{usenames,dvipsnames}{color}
\RequirePackage{color}
\RequirePackage{graphicx,pdfpages}  % to avoid conflicts with 'color'

% If the user uses the hyperref package, we pass some options to it...
% NB: to specify NO coloured links, pass the ``mono'' option to the class.
%	pdfpagelabels -- allow the PDF viewer to see \frontmatter numbers.
%   plainpages -- ensure we don't confuse linking with \frontmatter sections.
%   pdfborder -- ensure Adobe Reader doesn't draw links, even when the author
%           doesn't want them (i.e. doesn't pass ``colorlinks'').
%           Without this customisation, the reader will always draw boxes
%           around links, which is probably not what the author wanted.
%   pdfstartview -- make it easier to read on startup.
%   blue links -- these are easier on the eyes for most people and look
%           far less like errors.
%   breaklinks -- allows long links like big URLs to break accross lines.
%   linktocpage -- make only the page numbers in the ToC links; again
%           this is about being easier on the reader's eyes.
\definecolor{darkblue}{rgb}{0, 0, 0.5}
\definecolor{darkgreen}{rgb}{0, 0.5, 0}
\PassOptionsToPackage{pdfpagelabels,plainpages=false,bookmarksopen,bookmarksopenlevel=0,pdfborder={0 0 0},linkcolor=darkblue,citecolor=darkgreen,breaklinks=true,colorlinks,linktocpage,pdfstartview=FitH}{hyperref}

%%%
%%% Overrides
%%%
\renewcommand{\date}{%
    \ClassError{luthesis}{The \protect\date\space command should not be used}%
    {Alternative commands are provided for setting the date of the thesis and\MessageBreak
    the print date.  Please use them instead of \protect\date.}%
}
\AtBeginDocument{%
    \renewcommand{\bibname}{References}% for some reason this won't take effect unless done here.
}
\setcounter{secnumdepth}{5}
\setcounter{tocdepth}{5}


%%% titlepage text
\ifx\lt@year\@empty
\def\thesis@tptxt{{\Large A thesis \par}%
            \vskip 3em%
            {\large Submitted in fulfilment \par
		    of the \par}%
            \vskip 2em%
            {\Large Degree of Master Of Science in Internet Computing and Network Security\par%
            of\par%
            Loughborough University\par}%
            \vskip 5em}
\else
\def\thesis@tptxt{{\Large A thesis submitted in fulfilment of the degree of Master Of Science in Internet Computing and Network Security \par}%
            \vskip 3em%
            \vskip 5em%
            {\Large 
            \par%
            Loughborough University\par}%
            \vskip 5em}
\fi



%%%
%%% New Commands
%%%
\newcommand{\thesisDateDay}[1]{\def\@thesisDateDay{#1}}
\newcommand{\thesisDateMonth}[1]{\def\@thesisDateMonth{#1}}
\newcommand{\thesisDateYear}[1]{\def\@thesisDateYear{#1}}
\newcommand{\thesisSignedDay}[1]{\def\@thesisSignedDay{#1}}
\newcommand{\thesisSignedMonth}[1]{\def\@thesisSignedMonth{#1}}
\newcommand{\thesisSignedYear}[1]{\def\@thesisSignedYear{#1}}
% David Kastrup gave the following solution for repeating things n times -- http://groups.google.com/group/comp.text.tex/browse_thread/thread/1c9c1f99025c6f2b/7e2bd0b71066aa17?lnk=gst&q=repeating+sequence&rnum=4#7e2bd0b71066aa17
\def\recur#1{\csname rn#1\recur}\long\def\rnm#1{\endcsname{#1}#1}
\long\def\rn#1{}\def\repeatcom#1{\csname rn\expandafter\recur
\romannumeral\number\number#1 000\endcsname\endcsname} 
% Internal commands to simplify markup in forms...
\newcommand{\thesisFormTitle}[1]{%
    \noindent{\Large\textbf{#1}}\par%
}
%}

%%%
%%% \*matter Commands
%%%
\newif\if@frontmatter
\newcommand\frontmatter{%
    \cleardoublepage
    \@frontmattertrue}
	% setting pagenumbering to roman here would reset the counter
\newcommand\mainmatter{%
    \cleardoublepage
    \@frontmatterfalse
	\ifthenelse{\boolean{@iwp}}{%
		% don't try this at home!
		% there are good reasons why we separate the page numbering system
		% of the title/header/metadata pages from the rest!
	}{%
		% typographic convention is to separate the frontmatter (titles etc.)
		% from the rest by numbering them with roman numerals.  What we came
		% here to read starts from page 1 (arabic).
		\pagenumbering{arabic}
	}}
\newcommand\backmatter{%
    \if@openright
        \cleardoublepage
    \else
        \clearpage
    \fi
    \@frontmatterfalse}

%%%
%%% Templates
%%%
\definecolor{lupurple}{cmyk}{0.55, 0.80, 0.00, 0.64}
\definecolor{lupink}{cmyk}{0.00, 0.99, 0.49, 0.22}

\newcommand{\thesisCertificateHeader}{%
    \noindent\parbox{0.6\textwidth}{%
        \noindent\tiny%
        \textcolor{lupurple}{\textsf{Research Student Office, Academic Registry}}\\
        \textcolor{lupink}{\textsf{Loughborough University, Leicestershire, LE11 3TU, UK}}\\
        \textcolor{lupink}{\textsf{Switchboard: +44 (0)1509 263171~~Fax: +44 (0)1509 223938\\}}
    }\parbox{0.4\textwidth}{%
        \raggedleft
        \ifthenelse{\boolean{@mono}}{%
            \includegraphics[width=2in]{lufbra-black}%
        }{%
            \includegraphics[width=2in]{lufbra}%
        }
    }\par
}

\renewcommand{\maketitle}{%
    % Construct (textual) date variables...
    \def\@thesisDate{\@thesisDateDay\ \thesisMonthText{\@thesisDateMonth}\ \@thesisDateYear}%
    \def\@thesisSigned{\@thesisSignedDay\ \thesisMonthText{\@thesisSignedMonth}\ \@thesisSignedYear}%
	\ifthenelse{\boolean{@iwp}}{%
		% don't try this at home!
		% there are good reasons why we separate the page numbering system
		% of the title/header/metadata pages from the rest!
		\pagenumbering{arabic}
	}{%
		% typographic convention is to start numbering from i (frontmatter
		% pages are in roman numerals), but also to not show the page numbers
		% for the title page(s) as that's ugly.
		\pagenumbering{roman}
	}
	\pagestyle{empty}
        %%%
        %%% Thesis Access Form
        %%%
        \ifthenelse{\boolean{@access}}{%
            \includepdf{access}%
        }{}
    %\begin{titlepage}% -- we no longer use this because it screws up numbering.
        %\let\footnotesize\small%
        %\let\footnoterule\relax%
        %\let\footnote\thanks%
        \vspace*{\fill}%
        \begin{center}%
            {\LARGE \@title \par}%
            \vskip 3em%
            by
            \vskip 2em%
            {\Large
            \lineskip .75em%
            \begin{tabular}[t]{c}%
            \@author
            \end{tabular}\par}%
            \vskip 3em%
            \thesis@tptxt%
            {\large \@thesisDate \par}%
            \vskip 2em%
            {\small Copyright \@thesisDateYear\ \@author}%
        \end{center}\par%
        %\@thanks%
        \vspace*{\fill}%
		\vspace{25pt}% ``dubious hack no.1''
        \clearpage
    %\end{titlepage}
        %%%
        %%% Certificate of Originality
        %%%
        \ifthenelse{\boolean{@certorig}}{%
            \thesisCertificateHeader
            \vskip 9em
            \thesisFormTitle{Certificate of Originality}
            \vskip 3em
            {\noindent This is to certify that I am responsible for the work submitted in this thesis, that the original work is my own except as specified in acknowledgements or in footnotes, and that neither the thesis nor the original work contained therein has been submitted to this or any other institution for a higher degree.\par}
            \vskip 9em
            \noindent\repeatcom{16}{\ldots}\par
            \vskip 3em
            \noindent\@author\par
            \vskip 1em
            \noindent\@thesisSigned\par
            \clearpage
        }{}
    %\end{titlepage}
    %%%
    %%% Tidy up...
	%%% (No longer needed as we aren't using titlepage no more! :-)
    %%%
%    \setcounter{footnote}{0}
%    \global\let\thanks\relax
%    \global\let\maketitle\relax
%    \global\let\@thanks\@empty
%    \global\let\@author\@empty
%    \global\let\@date\@empty
%    \global\let\@title\@empty
%    \global\let\title\relax
%    \global\let\author\relax
%    \global\let\date\relax
%    \global\let\and\relax
	\pagestyle{headings}
}

%%%
%%% \frontmatter-aware Chapter Heads and TOC Entries
%%%
\def\@chapter[#1]#2{\ifnum \c@secnumdepth >\m@ne
        \if@frontmatter\else\refstepcounter{chapter}\fi%
        \typeout{\@chapapp\space\thechapter.}%
    	% luthesis: must behave differently if in frontmatter...
        \if@frontmatter%
    		% Are we using hyperref?
    		\ifthenelse{\isundefined{\texorpdfstring}}{%
    			% No -- do nowt.
    		}{%
    			% Yes -- add a phantom section first...
    			\phantomsection
    		}%
    		% Either way, add the contents line...
    		\addcontentsline{toc}{chapter}{#1}%
        \else
           \addcontentsline{toc}{chapter}%
    			{\protect\numberline{\thechapter}#1}%
        \fi
   \else
     \addcontentsline{toc}{chapter}{#1}%
   \fi
   \chaptermark{#1}%
   \addtocontents{lof}{\protect\addvspace{10\p@}}%
   \addtocontents{lot}{\protect\addvspace{10\p@}}%
   \if@twocolumn
     \@topnewpage[\@makechapterhead{#2}]%
   \else
     \if@frontmatter\@makeschapterhead{#2}\else\@makechapterhead{#2}\fi%
     \@afterheading
   \fi}

%%%
%%% Utility Macros
%%%
\newcommand{\thesisMonthText}[1]{%
    \ifcase#1%
    \or{January}%
    \or{February}%
    \or{March}%
    \or{April}%
    \or{May}%
    \or{June}%
    \or{July}%
    \or{August}%
    \or{September}%
    \or{October}%
    \or{November}%
    \or December\fi}

\AtBeginDocument{
	% Are we using hyperref?
	\ifthenelse{\isundefined{\texorpdfstring}}{%
		% No -- do nowt.
	}{%
		% Yes -- provide extra \autoref commands...
		\let\orgautoref\autoref
	
		% \autoref is for inside a sentence
		% This represents the standard hyperref names according to http://www.tex.ac.uk/tex-archive/macros/latex/contrib/hyperref/doc/manual.html at the time of writing.  They are explicitly declared here for ease of maintenance.
		\renewcommand{\autoref}{%
			\def\figureautorefname{Figure}%
			\def\tableautorefname{Table}%
			\def\partautorefname{Part}%
			\def\appendixautorefname{Appendix}%
			\def\equationautorefname{Equation}%
			\def\Itemautorefname{item}%
			\def\chapterautorefname{chapter}%
			\def\sectionautorefname{section}
			\def\subsectionautorefname{subsection}%
			\def\subsubsectionautorefname{subsubsection}%
			\def\paragraphautorefname{paragraph}%
			\def\Hfootnoteautorefname{footnote}%
			\def\AMSautorefname{Equation}%
			\def\theoremautorefname{Theorem}%
			\def\pageautorefname{page}%
			% This one is extra...
			\def\subfigureautorefname{Figure}%
			% Extra for algorithms bundle...
			\def\algorithmautorefname{algorithm}%
			\leavevmode\unskip \orgautoref}
		
		% \autorefs is plural for inside a sentence
		\providecommand{\autorefs}{%
			\def\figureautorefname{Figures}%
			\def\tableautorefname{Tables}%
			\def\partautorefname{Parts}%
			\def\appendixautorefname{Appendices}%
			\def\equationautorefname{Equations}%
			\def\Itemautorefname{items}%
			\def\chapterautorefname{chapters}%
			\def\sectionautorefname{sections}
			\def\subsectionautorefname{subsections}%
			\def\subsubsectionautorefname{subsubsections}%
			\def\paragraphautorefname{paragraphs}%
			\def\Hfootnoteautorefname{footnotes}%
			\def\AMSautorefname{Equations}%
			\def\theoremautorefname{Theorems}%
			\def\pageautorefname{pages}%
			% This one is extra...
			\def\subfigureautorefname{Figures}%
			% Extra for algorithms bundle...
			\def\algorithmautorefname{algorithms}%
			\leavevmode\unskip \orgautoref}
		
		% \Autoref is for the beginning of the sentence
		\newcommand{\Autoref}{%
			\def\figureautorefname{Figure}%
			\def\tableautorefname{Table}%
			\def\partautorefname{Part}%
			\def\appendixautorefname{Appendix}%
			\def\equationautorefname{Equation}%
			\def\Itemautorefname{Item}%
			\def\chapterautorefname{Chapter}%
			\def\sectionautorefname{Section}
			\def\subsectionautorefname{Subsection}%
			\def\subsubsectionautorefname{Subsubsection}%
			\def\paragraphautorefname{Paragraph}%
			\def\Hfootnoteautorefname{Footnote}%
			\def\AMSautorefname{Equation}%
			\def\theoremautorefname{Theorem}%
			\def\pageautorefname{Page}%
			% This one is extra...
			\def\subfigureautorefname{Figure}%
			% Extra for algorithms bundle...
			\def\algorithmautorefname{Algorithm}%
			\leavevmode\unskip \orgautoref}
		
		% \Autorefs is plural for the beginning of the sentence
		\providecommand{\Autorefs}{%
			\def\figureautorefname{Figures}%
			\def\tableautorefname{Tables}%
			\def\partautorefname{Parts}%
			\def\appendixautorefname{Appendices}%
			\def\equationautorefname{Equations}%
			\def\Itemautorefname{Items}%
			\def\chapterautorefname{Chapters}%
			\def\sectionautorefname{Sections}%
			\def\subsectionautorefname{Subsections}%
			\def\subsubsectionautorefname{Subsubsections}%
			\def\paragraphautorefname{Paragraphs}%
			\def\Hfootnoteautorefname{Footnotes}%
			\def\AMSautorefname{Equations}%
			\def\theoremautorefname{Theorems}%
			\def\pageautorefname{Pages}%
			% This one is extra...
			\def\subfigureautorefname{Figures}%
			% Extra for algorithms bundle...
			\def\algorithmautorefname{Algorithms}%
			\leavevmode\unskip \orgautoref}
	}%
}
