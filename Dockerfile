# File: Dockerfile
FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential clang clang-format cmake gdb lldb \
    libssl-dev pkg-config \
    curl wget netcat-openbsd iproute2 iputils-ping dnsutils \
    apache2-utils siege openssl \
    python3 python3-pip python3-venv \
    valgrind strace lsof \
    vim nano git ca-certificates zsh \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth=1 https://github.com/ohmybash/oh-my-bash ~/.oh-my-bash \
 && cp ~/.oh-my-bash/templates/bashrc.osh-template ~/.bashrc \
 && sed -i 's/^OSH_THEME=.*/OSH_THEME="font"/' ~/.bashrc

# Minimal zsh config (quality-of-life)
RUN printf '%s\n' \
  'HISTFILE=~/.zsh_history' \
  'setopt HIST_IGNORE_ALL_DUPS SHARE_HISTORY' \
  'autoload -Uz compinit && compinit' \
  'bindkey -e' \
  'alias ll="ls -alF"' \
  'alias la="ls -A"' \
  > ~/.zshrc

# Expose common web ports
EXPOSE 80 443 8000 8080 8081

# Default command: zsh (you’ll land in zsh)
CMD ["/usr/bin/zsh"]
