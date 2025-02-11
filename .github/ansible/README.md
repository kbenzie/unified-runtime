# Ansible

The repository contains various Ansible playbooks to aid with the installation
and removal of development packages, tools, etc. which may be necessary when
working on the oneAPI software stack.

## Install Ansible

This command will install the Ansible package into `~/.local` and its
command-line interface into `~/.local/bin`. If you have not already adding
`~/.local/bin` to your `PATH` environment variable, do that now.

```console
$ pip install --user ansible jmespath
```

## Intel GPU Compute Drivers

To install the Intel OpenCL GPU driver and Intel Level-Zero GPU driver using the
following command to run the Ansible playbook. The `--ask-become-pass` argument
will prompt you to enter the "become" password, this is the password required to
"become" the `root` user, e.g. via `sudo`.

```console
$ ansible-playbook playbooks/install-intel-opencl-level-zero-gpu.yaml --ask-become-pass
```

To remove these packages, use the following command.

```console
$ ansible-playbook playbooks/remove-intel-opencl-level-zero-gpu.yaml --ask-become-pass
```

> Note: To override the default intel/llvm ref of `refs/heads/sycl` use the
> `DPCXX_REF` environment variable, accepts any ref that works with a GitHub
> raw content URL, e.g. a commit or `refs/heads/<branch-name>`.
