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
# if [[ $term = "st" ]]; then
#     transset-df "0.85" --id "$WINDOWID" >/dev/null
# fi

#------------------------------------------------------------

## Aliases for the functions above.
## Uncomment an alias if you want to use it.
##

# alias ef='_open_files_for_editing'     # 'ef' opens given file(s) for editing
# alias pacdiff=eos-pacdiff
################################################################################
alias cowjoke='curl -s https://official-joke-api.appspot.com/jokes/programming/random# | jq -r ".[0].setup, .[0].punchline" | cowsay'
alias v='nvim'
alias h='helix'
alias tmux="TERM=screen-256color-bce tmux"
alias nf='neofetch --ascii_distro arch'
alias pn='ping gnu.org'
alias scb='source .bashrc'
alias tatt='tmux attach-session -t'
alias lg='lazygit'

# environment for Directory
################################################################################
export ITCC='cd /home/gricowijaya/Documents/Project/itcc/itcc-2022'
export CAKEPLABS='cd /home/gricowijaya/Documents/Cakeplabs/Task'
export CTF='cd /home/gricowijaya/Documents/CTF'
export KULIAH='cd /home/gricowijaya/Documents/Kuliah'
export PRAKTIKUMPEMROG='cd /home/gricowijaya/Documents/Kuliah/Praktikum-Pemrograman/SemesterV'
export BINAR='cd /home/gricowijaya/Documents/Kuliah/SemesterV/BinarAcademy'
export DOC='cd /home/gricowijaya/Documents/DeveloperDocumentation'
export HDMI='cd /home/gricowijaya/.screenlayout; ./monitor_1.sh; cd /home/gricowijaya'
export SUCKLESS='cd /home/gricowijaya/.local/src'
export MUSIC='cd /home/gricowijaya/Music'
export PRIMEFLIGHT='cd /home/gricowijaya/Documents/Kuliah/SemesterV/BinarAcademy/chapter/ch9-11'

## SOURCE FZF
source /usr/share/fzf/completion.bash
source /usr/share/fzf/key-bindings.bash

## STARSHIP
# eval "$(starship init bash)"

# Custom Bash Prompt
# get current branch in git repo
# function parse_git_branch() {
# 	BRANCH=`git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/\1/'`
# 	if [ ! "${BRANCH}" == "" ]
# 	then
# 		STAT=`parse_git_dirty`
# 		echo "[${BRANCH}${STAT}]"
# 	else
# 		echo ""
# 	fi
# }

# # get current status of git repo
# export PS1="  \W \[\e[31;40m\]\`parse_git_branch\`\[\e[m\]$ "

#echo 
#echo
# echo "GNU(R) ARCH 05"
# echo "   (C) Judd Vinet, Aaron Griffin 2002"
#echo

# Go Programming
export GOPATH="/home/gricowijaya/go/"
export PATH="$PATH:/home/gricowijaya/go/bin"

# Default Terminal Editor
export EDITOR="nvim"

# REMOVE BG https://www.remove.bg/
export REMOVE_BG_API_KEY=ckpR5iWeKp2go57yG1rjW3ub  

# Node Version Manager
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion
