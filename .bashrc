#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

[[ -f ~/.welcome_screen ]] && . ~/.welcome_screen

_set_liveuser_PS1() {
    PS1='[\u@\h \W]\$ '
    if [ "$(whoami)" = "liveuser" ] ; then
        local iso_version="$(grep ^VERSION= /usr/lib/endeavouros-release 2>/dev/null | cut -d '=' -f 2)"
        if [ -n "$iso_version" ] ; then
            local prefix="eos-"
            local iso_info="$prefix$iso_version"
            PS1="[\u@$iso_info \W]\$ "
        fi
    fi
}
_set_liveuser_PS1
unset -f _set_liveuser_PS1

ShowInstallerIsoInfo() {
    local file=/usr/lib/endeavouros-release
    if [ -r $file ] ; then
        cat $file
    else
        echo "Sorry, installer ISO info is not available." >&2
    fi
}


alias ls='ls --color=auto'
alias ll='ls -lavh --ignore=..'   # show long listing of all except ".."
alias l='ls -lav --ignore=.?*'   # show long listing but no hidden dotfiles except "."

[[ "$(whoami)" = "root" ]] && return

[[ -z "$FUNCNEST" ]] && export FUNCNEST=100          # limits recursive functions, see 'man bash'

## Use the up and down arrow keys for finding a command in history
## (you can write some initial letters of the command first).
bind '"\e[A":history-search-backward'
bind '"\e[B":history-search-forward'

################################################################################
## Some generally useful functions.
## Consider uncommenting aliases below to start using these functions.
##
## October 2021: removed many obsolete functions. If you still need them, please look at
## https://github.com/EndeavourOS-archive/EndeavourOS-archiso/raw/master/airootfs/etc/skel/.bashrc

_open_files_for_editing() {
    # Open any given document file(s) for editing (or just viewing).
    # Note1:
    #    - Do not use for executable files!
    # Note2:
    #    - Uses 'mime' bindings, so you may need to use
    #      e.g. a file manager to make proper file bindings.

    if [ -x /usr/bin/exo-open ] ; then
        echo "exo-open $@" >&2
        setsid exo-open "$@" >& /dev/null
        return
    fi
    if [ -x /usr/bin/xdg-open ] ; then
        for file in "$@" ; do
            echo "xdg-open $file" >&2
            setsid xdg-open "$file" >& /dev/null
        done
        return
    fi

    echo "$FUNCNAME: package 'xdg-utils' or 'exo' is required." >&2
}

# get what terminal is it 
term="$(cat /proc/$PPID/comm)"

# set transparent st
if [[ $term = "st" ]]; then
    transset-df "0.90" --id "$WINDOWID" >/dev/null
fi

#------------------------------------------------------------

## Aliases for the functions above.
## Uncomment an alias if you want to use it.
##

# alias ef='_open_files_for_editing'     # 'ef' opens given file(s) for editing
# alias pacdiff=eos-pacdiff
################################################################################
alias v='nvim'
alias vi='nvim'
alias tmux="TERM=screen-256color-bce tmux"
alias nf='neofetch --ascii_distro arch'
alias rn='sudo systemctl restart NetworkManager'
alias pn='ping gnu.org'
# alias itcc='cd /home/gricowijaya/Documents/Project/itcc/itcc-2022/; ide'
alias itcc='cd /home/gricowijaya/Documents/Project/itcc/itcc-2022/; v'
alias vitcc='cd /home/gricowijaya/Documents/Project/itcc/itcc-2022/;'
alias kantor='cd /home/gricowijaya/Documents/Cakeplabs/Task/'
alias ctf='cd /home/gricowijaya/Documents/CTF/'
alias practice='cd /home/gricowijaya/Documents/Practice'
alias kuliah='cd /home/gricowijaya/Documents/Kuliah/'
alias binar='cd /home/gricowijaya/Documents/Kuliah/SemesterV/BinarAcademy/'
alias buildit='cd /home/gricowijaya/Documents/Kuliah/BuildIT2022'
alias doc='cd /home/gricowijaya/Documents/DeveloperDocumentation/'
alias hdmi='cd /home/gricowijaya/.screenlayout; ./monitor_1.sh; cd /home/gricowijaya'
alias edp1='cd /home/gricowijaya/.screenlayout; ./edp1.sh; cd /home/gricowijaya'
alias eright='cd /home/gricowijaya/.screenlayout; ./extend_right.sh; cd /home/gricowijaya'
alias eleft='cd /home/gricowijaya/.screenlayout; ./extend_left.sh; cd /home/gricowijaya'
alias sl='cd /home/gricowijaya/.local/src/; v .'
alias scb='source .bashrc'
alias tatt='tmux attach-session -t'
alias lg='lazygit'
# alias fduck='firefox duck.com' 
# alias fyt='firefox youtube.com'
# alias fgo='firefox google.com'


source /usr/share/fzf/completion.bash
source /usr/share/fzf/key-bindings.bash
# eval "$(starship init bash)"
## Emulate an MS-DOS prompt in your Linux shell.
## Laszlo Szathmary (jabba.laci@gmail.com), 2011
## Project home page:
## https://ubuntuincident.wordpress.com/2011/02/08/emulate-the-ms-dos-prompt/
##
##
## Modified by Soldier of Fortran
##
## Add to you ~/.bashrc file with: 'source ~/.themes/95/bashrc'

#function msdos_pwd
#{
#    local dir="`pwd`"

#    echo $dir | tr '/' '\\'
#}

#export PS1='C:`msdos_pwd`> '

# Custom Bash Prompt
# get current branch in git repo
function parse_git_branch() {
	BRANCH=`git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/\1/'`
	if [ ! "${BRANCH}" == "" ]
	then
		STAT=`parse_git_dirty`
		echo "[${BRANCH}${STAT}]"
	else
		echo ""
	fi
}

# get current status of git repo
function parse_git_dirty {
	status=`git status 2>&1 | tee`
	dirty=`echo -n "${status}" 2> /dev/null | grep "modified:" &> /dev/null; echo "$?"`
	untracked=`echo -n "${status}" 2> /dev/null | grep "Untracked files" &> /dev/null; echo "$?"`
	ahead=`echo -n "${status}" 2> /dev/null | grep "Your branch is ahead of" &> /dev/null; echo "$?"`
	newfile=`echo -n "${status}" 2> /dev/null | grep "new file:" &> /dev/null; echo "$?"`
	renamed=`echo -n "${status}" 2> /dev/null | grep "renamed:" &> /dev/null; echo "$?"`
	deleted=`echo -n "${status}" 2> /dev/null | grep "deleted:" &> /dev/null; echo "$?"`
	bits=''
	if [ "${renamed}" == "0" ]; then
		bits=">${bits}"
	fi
	if [ "${ahead}" == "0" ]; then
		bits="*${bits}"
	fi
	if [ "${newfile}" == "0" ]; then
		bits="+${bits}"
	fi
	if [ "${untracked}" == "0" ]; then
		bits="?${bits}"
	fi
	if [ "${deleted}" == "0" ]; then
		bits="x${bits}"
	fi
	if [ "${dirty}" == "0" ]; then
		bits="!${bits}"
	fi
	if [ ! "${bits}" == "" ]; then
		echo " ${bits}"
	else
		echo ""
	fi
}

export PS1=" \W \[\e[31;40m\]\`parse_git_branch\`\[\e[m\]  "

#echo 
#echo
# echo "GNU(R) ARCH 05"
# echo "   (C) Judd Vinet, Aaron Griffin 2002"
#echo

# Go Programming
export GOPATH="/home/gricowijaya/go/"
export PATH="$PATH:/home/gricowijaya/go/bin"
export EDITOR="nvim"

# Node Version Manager
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
