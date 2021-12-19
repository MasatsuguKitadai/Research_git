%%タイトル
%% \title{}：タイトル名
%% \secondtitle{}：タイトル名（2段目）
%% \date{}：提出年
%% \studentid{}：学籍番号
%% \studentname{}：学生の名前
%% \teachername{}：担当教員の名前
%%
%%
%%
%%
%%
%%
%%
\NeedsTeXFormat{pLaTeX2e}
\ProvidesClass{jsarticle_measlab_3}
[2015/01/27 tani update]
\LoadClassWithOptions{jsarticle} %jsarticleが元なのでファイルが必要
\usepackage{tocloft}
%変更点 sectionの見出しにピリオド
\renewcommand{\thesection}{\presectionname\@arabic\c@section.\postsectionname}

%変更点　bibtex等で作成した参考文献を目次に反映
\renewenvironment{thebibliography}[1]{%
	\addcontentsline{toc}{section}{\refname}%
	\global\let\presectionname\relax
	\global\let\postsectionname\relax
	\section*{\refname}\@mkboth{\refname}{\refname}%
	\list{\@biblabel{\@arabic\c@enumiv}}%
	{\settowidth\labelwidth{\@biblabel{#1}}%
		\leftmargin\labelwidth
		\advance\leftmargin\labelsep
		\@openbib@code
		\usecounter{enumiv}%
		\let\p@enumiv\@empty
		\renewcommand\theenumiv{\@arabic\c@enumiv}}%
	\sloppy
	\clubpenalty4000
	\@clubpenalty\clubpenalty
	\widowpenalty4000%
	\sfcode`\.\@m}

%変更点 図→Fig 表→Table
\renewcommand{\figurename}{Fig.\ }
\renewcommand{\tablename}{Table }

%変更点　タイトル　
\if@titlepage
\renewcommand{\maketitle}{%
	\begin{titlepage}%
		\let\footnotesize\small
		\let\footnoterule\relax
		\let\footnote\thanks
		\null\vfil
		\if@slide
		{\footnotesize \@date}%
		\begin{center}
			\mbox{} \\[1zw]
			\large
			{\maybeblue\hrule height0pt depth2pt\relax}\par
			\smallskip
			\@title
			\smallskip
			{\maybeblue\hrule height0pt depth2pt\relax}\par
			\vfill
			{\small \@author}%
		\end{center}
		\else
		\vskip 60\p@
		\begin{center}%
			{\LARGE \@title \par}%
			\vskip 3em%
			{\large
				\lineskip .75em
				\begin{tabular}[t]{c}%
					\@author
				\end{tabular}\par}%
			\vskip 1.5em
			{\large \@date \par}%
		\end{center}%
		\fi
		\par
		\@thanks\vfil\null
	\end{titlepage}%
	\setcounter{footnote}{0}%
	\global\let\thanks\relax
	\global\let\maketitle\relax
	\global\let\@thanks\@empty
	\global\let\@author\@empty
	\global\let\@date\@empty
	\global\let\@title\@empty
	\global\let\title\relax
	\global\let\author\relax
	\global\let\date\relax
	\global\let\and\relax
	\global\let\@studentid\@empty % 追加
	\global\let\studentid\relax % 追加
	\global\let\@studentname\@empty % 追加
	\global\let\studentname\relax % 追加
	\global\let\@teachername\@empty % 追加
	\global\let\teachername\relax % 追加
}%
\else
\renewcommand{\maketitle}{\par
	\begingroup
	\renewcommand\thefootnote{\@fnsymbol\c@footnote}%
	\def\@makefnmark{\rlap{\@textsuperscript{\normalfont\@thefnmark}}}%
	\long\def\@makefntext##1{\advance\leftskip 3zw
		\parindent 1zw\noindent
		\llap{\@textsuperscript{\normalfont\@thefnmark}\hskip0.3zw}##1}%
	\if@twocolumn
	\ifnum \col@number=\@ne
	\@maketitle
	\else
	\twocolumn[\@maketitle]%
	\fi
	\else
	\newpage
	\global\@topnum\z@  % Prevents figures from going at top of page.
	\@maketitle
	\fi
	\plainifnotempty
	\@thanks
	\endgroup
	\setcounter{footnote}{0}%
	\global\let\thanks\relax
	\global\let\maketitle\relax
	\global\let\@thanks\@empty
	\global\let\@author\@empty
	\global\let\@date\@empty
	\global\let\@title\@empty
	\global\let\@secondtitle\@empty
	\global\let\title\relax
	\global\let\secondtitle\relax
	\global\let\author\relax
	\global\let\date\relax
	\global\let\and\relax
	\global\let\@studentid\@empty % 追加
	\global\let\studentid\relax % 追加
	\global\let\@studentname\@empty % 追加
	\global\let\studentname\relax % 追加
	\global\let\@teachername\@empty % 追加
	\global\let\teachername\relax % 追加	
	\global\let\@secondteachername\@empty % 追加
	\global\let\secondteachername\relax % 追加
}
\def\@maketitle{%以下タイトルのレイアウト部分
	\newpage\null
	\vskip 10truept
	\begin{center}%
		\let\footnote\thanks
		{\LARGE 令和\@date 年度 \par}%
		\vskip 33.5truept
		{\large
			\begin{tabular}[t]{c}%
				\Huge 卒  業  論  文
			\end{tabular}\par}%
		\vskip 33.5truept
		\LARGE 題　 目 \par
		\vskip 32truept
			\begin{tabular}[t]{c}%
				\Huge  \gt \@title\\
				\hline\vspace{20truept}
				\\
				\Huge \gt \@secondtitle\\
				\hline
			\end{tabular}
		
		\vskip 63truept
	\end{center}%
	
	\begin{tabular}{l@{\hspace{9truemm}}c}%
		\Large 学籍番号 & \LARGE{ \bf\@studentid} \\
		\cline{2-2}\vspace{20truept}\\
		\Large 提 出 者 & \LARGE{ \bf\@studentname}\\
		\cline{2-2}\vspace{40truept}\\
		\Large 指導教員 & \LARGE{ \bf ~~~~~\@teachername~~~~~}\\
		\cline{2-2}	\\
		\Large 指導教員 & \LARGE{ \bf ~~~~~\@secondteachername~~~~~}\\
		\cline{2-2}
	\end{tabular}
	\vskip 34truept
	\begin{center}
		\Large 京都工芸繊維大学 工芸科学部\par
		\vskip 16truept
		\Large 機械システム工学課程\par
	\end{center}
	\par\vskip 1.5em
	\ifvoid\@abstractbox\else\centerline{\box\@abstractbox}\vskip1.5em\fi
	\pagestyle{empty}
	\newpage
	\setcounter{page}{1}
}
\long\def\studentid#1{\long\gdef\@studentid{#1}}
\long\def\studentname#1{\long\gdef\@studentname{#1}}
\long\def\teachername#1{\long\gdef\@teachername{#1}}
\long\def\secondteachername#1{\long\gdef\@secondteachername{#1}}
\long\def\secondtitle#1{\long\gdef\@secondtitle{#1}}
\fi

%変更点　余白
\setlength{\textwidth}{170truemm} 
\setlength{\textheight}{252truemm}
\setlength{\oddsidemargin}{30truemm}
\addtolength{\oddsidemargin}{-1truein}
\setlength\topmargin{25truemm}
\addtolength\topmargin{-1truein}
\setlength{\hoffset}{0truemm}
\setlength{\headheight}{0truemm}
\setlength{\marginparsep}{0truemm}
\setlength{\footskip}{10truemm} %ページ番号位置
\setlength{\headsep}{0truemm}

%変更点　目次
\renewcommand{\contentsname}{\LARGE 目次} %目次のサイズ変更
\setcounter{tocdepth}{3} %階層をsubsectionまで
\renewcommand{\cftdot}{$\cdot$} %.から点 に

\newcommand{\Thesection}[1]{\section*{#1} %Thesection 宣言には数字がつかないように
\addcontentsline{toc}{section}{#1}} %目次に追加
\renewcommand*{\l@section}{\@dottedtocline{1}{0zw}{3zw}} %sectionを他と同じ扱いに
\renewcommand*{\l@subsection}   {\@dottedtocline{2}{0zw}{3zw}} %sectionと同じ位置に
\renewcommand*{\l@subsubsection}{\@dottedtocline{3}{1zw}{3zw}}%sectionから一文字ずらす
\def\numberline#1{\hb@xt@\@lnumwidth{#1\hfil}\hspace{0pt}} %数字の後のスペース作成

%変更点　引用を[1]ではなく(1)にする
\def\@cite#1{\textsuperscript{(#1)}}

%変更点　太線追加 \Hlineで呼び出し
  \def\Hline{
  	\noalign{\ifnum0=`}\fi\hrule \@height 4.\arrayrulewidth \futurelet
  	\reserved@a\@xhline}