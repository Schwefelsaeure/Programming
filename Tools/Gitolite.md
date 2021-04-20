# Gitolite

- Website: http://gitolite.com/gitolite/
- Purpose: Gitolite allows you to setup git hosting on a central server, with fine-grained access control and many more powerful features.

## Overview

- Gitolite uses ***sshd*** (or alternatively ***httpd***) for authentication. Then, Gitolite uses ***gitlite-shell*** to check autorisation of request (i.e., is user **Foo** allowed to read/write repo **Bar**).
- Gitolite uses special admin repo ***gitolite-admin*** to create and manage repos (i.e., clone it, modify ***conf/gitolite*** and ***keydir*** and push it back).
- Gitolite uses one single hosting using on the server (usually **git** which is a real Linux user created by in shell by ***adduser***). Repo users do **not** get an own Linux user account. Instead, they are only visible to Gitolite (and authenticated by their public key).

## Special Use Cases

- Run ***gitolite setup*** after copying existing repos to Gitolite server (e.g., when getting a new server).
- When running ***sshd*** on a non-default port (22), a ***.ssh/conf*** is required (so that correct port is used).

  **Note:**
  - Gitolite requires SCP-like syntax when interacting with repos. I.e. ***git clone user@host:repo_name.git*** (colon separates host and path).
  - **Gitolite does not accept an usual URI**! E.g., ***git clone ssh://user@host:port/home/git/repositories/repo_name.git***).