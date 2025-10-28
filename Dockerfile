# syntax=docker/dockerfile:1
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive TZ=UTC ZSH="/root/.oh-my-zsh"

# Toolchain, net utils, SSH, sudo, shells, siege
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential clang clang-format cmake gdb lldb \
    libssl-dev pkg-config \
    curl wget ca-certificates git \
    netcat-openbsd iproute2 iputils-ping dnsutils \
    apache2-utils siege openssl \
    python3 python3-pip python3-venv \
    valgrind strace lsof \
    vim nano tmux less \
    zsh sudo openssh-server \
 && rm -rf /var/lib/apt/lists/*

# ---------- SSHD setup ----------
RUN mkdir -p /var/run/sshd \
  && sed -i 's/^#\?PasswordAuthentication .*/PasswordAuthentication yes/' /etc/ssh/sshd_config \
  && sed -i 's/^#\?PermitRootLogin .*/PermitRootLogin yes/' /etc/ssh/sshd_config \
  && sed -i 's/^#\?PubkeyAuthentication .*/PubkeyAuthentication yes/' /etc/ssh/sshd_config

# ---------- Users (root + leet; passwords = 1337) ----------
RUN useradd -m -s /usr/bin/zsh leet \
  && echo 'leet:1337' | chpasswd \
  && echo 'root:1337' | chpasswd \
  && usermod -aG sudo leet \
  && printf "leet ALL=(ALL) NOPASSWD:ALL\n" >/etc/sudoers.d/90-leet-nopasswd \
  && chmod 440 /etc/sudoers.d/90-leet-nopasswd \
  && usermod -s /usr/bin/zsh root

# ---------- Oh My Zsh for root & leet ----------
ENV ZSH_THEME="robbyrussell"
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended \
 && git clone --depth=1 https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-autosuggestions \
 && git clone --depth=1 https://github.com/zsh-users/zsh-syntax-highlighting ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting \
 && sed -i 's/^plugins=(git)$/plugins=(git zsh-autosuggestions zsh-syntax-highlighting)/' /root/.zshrc \
 && cp -a /root/.oh-my-zsh /home/leet/.oh-my-zsh \
 && cp -a /root/.zshrc /home/leet/.zshrc \
 && chown -R leet:leet /home/leet/.oh-my-zsh /home/leet/.zshrc

# ---------- Workdir & ports ----------
WORKDIR /workspace
EXPOSE 20 22 80 443 8000 8080 8081

# ---------- PID 1: sshd in foreground (no extra script) ----------
CMD bash -lc 'if [ ! -f /etc/ssh/ssh_host_rsa_key ]; then ssh-keygen -A; fi; exec /usr/sbin/sshd -D'
