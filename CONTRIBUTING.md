# Your first contribution

You do not need to know sockets or telnet before you start. Pick a task, read its
linked references, and build one small piece. If you're stuck, put the command,
error, and what you tried in the issue so someone can help.

## 1. Get a copy in Codespaces

1. Sign in to GitHub and [fork this repository](https://github.com/A-Programming-Club/nyancat-network/fork)
   into your own account. A **fork** is your GitHub copy.
2. Open your fork. Click **Code → Codespaces → Create codespace on main**.
3. Wait for setup to finish, then open **Terminal → New Terminal**.

Codespaces has already **cloned** your fork: you now have working files and Git
history inside a Linux computer in your browser. Do not clone again inside it.

Run:

```bash
git remote -v
git status
```

`origin` should point to **your fork**. Add the club repository as `upstream` if
`git remote -v` does not already show it:

```bash
git remote add upstream https://github.com/A-Programming-Club/nyancat-network.git
```

If you already opened a Codespace on the club repository and have write access,
you can use it: add that same `upstream`, and push your feature branch to `origin`.
If you do not have write access, start from your fork as above.

### What does cloning look like outside Codespaces?

On a Linux machine with Git, GCC 13+, CMake 3.25+, and Ninja installed, replace
`YOUR_USERNAME` below with your GitHub username:

```bash
git clone https://github.com/YOUR_USERNAME/nyancat-network.git
cd nyancat-network
git remote add upstream https://github.com/A-Programming-Club/nyancat-network.git
```

The Codespace also installs the server tools; use it for the default workflow.

## 2. Claim an issue and make a branch

Choose a task from the [roadmap](docs/roadmap.md), read its links, and comment
“I'd like this one.” An organizer assigns it to avoid duplicate work. A task's
dependencies should be merged before you start implementing against them.

With a clean working tree (`git status`), update your local `main`:

```bash
git switch main
git pull --ff-only upstream main
git push origin main
git switch -c 2-parse-cli
```

Replace `2-parse-cli` with your issue number and a short description. A **branch**
keeps your work separate until it is ready to merge. Keep `main` for merged work.

## 3. Change code and check it

Read [the shared design](docs/design.md) and [our C++ style](docs/style.md),
implement your issue, and run:

```bash
cmake --preset dev
python3 scripts/lint.py --fix
cmake --build --preset dev
ctest --preset dev
```

These commands configure the build, format/check C++ style, compile, and run
registered tests. `--fix` applies formatting; naming errors need manual fixes.
CI runs `python3 scripts/lint.py` without changing files. The initial scaffold
has no client tests yet. Add meaningful tests with your implementation using
[tests/README.md](tests/README.md).

Clangd provides completion, diagnostics, and formatting on save in Codespaces.
If you created your Codespace before this tooling was added, use **Rebuild
Container** from the command palette once to install it.

Use the Linux manual in the terminal when a reference names a function:

```bash
man 2 recv
man 3 getaddrinfo
```

In a manual, `/EINTR` searches, `n` finds the next match, and `q` quits. Look for
the declaration, return value, and error cases. Read the relevant section, try a
small experiment, then use what you learned. You should be able to explain the
code you submit, including code produced with help from another person or a tool.

## 4. Commit, then push

**Saving a file** changes your working files. **Committing** records a local
snapshot. **Pushing** uploads your commits to GitHub.

```bash
git status
git diff
git add src/cli.cpp
```

That `git add` line is an example; stage each source, header, test, or build file
you actually changed. Do not stage `build/` or compiled programs. Then:

```bash
git diff --cached
git commit -m "Parse the client host and port"
git push -u origin HEAD
```

If Git asks for your identity, set your own name and GitHub-associated email:

```bash
git config user.name "Your Name"
git config user.email "YOUR_GITHUB_EMAIL"
```

Your GitHub **Settings → Emails** page also offers a private `noreply` address.

## 5. Make a pull request (PR)

Open the link printed by `git push`, or click **Compare & pull request** on your
fork. Choose **base repository: A-Programming-Club/nyancat-network**,
**base: main**, and **compare: your feature branch**.

Use a title describing your change. In the description include:

- `Closes #2` (your actual issue number).
- What changed and the commands/results you checked.
- A documentation link and what it helped you understand.

Create the PR, wait for **Build and check**, and ask a club organizer for review.
First-time contributors may need an organizer to approve the Actions run.
For a build failure, open the check's logs and find the first actual error.

To address feedback, edit on the same branch, commit, and run `git push` again.
The existing PR updates automatically. A **merge** adds the approved changes to
the club's `main`; an organizer will handle that after review.

## 6. Bring in other people's changes

**Pulling** downloads commits and integrates them. When updating a feature branch,
first commit your current work, then:

```bash
git fetch upstream
git merge upstream/main
```

If Git reports a conflict, open each named file, choose the correct combined
result, and remove the `<<<<<<<`, `=======`, and `>>>>>>>` markers. Then:

```bash
git add path/to/resolved-file.cpp
git commit
cmake --preset dev
python3 scripts/lint.py --fix
cmake --build --preset dev
ctest --preset dev
git push
```

Use the actual file path. If you're unsure how to resolve a conflict,
`git merge --abort` returns to the pre-merge state; ask for help. A rejected push
or failed `--ff-only` pull is also a reason to stop and inspect, not force-push.

After your PR is merged, update `main` with the three commands from step 2, then
create a fresh branch for your next issue. Keep changes on one issue per PR unless
the organizer agrees the tasks belong together.

When finished for the day, commit and push work you want to keep, then stop your
Codespace from [github.com/codespaces](https://github.com/codespaces). Stopping
keeps its files; deleting removes the environment, including unpushed work.

## References

- [Git handbook: clone, branch, commit, pull, push](https://docs.github.com/en/get-started/using-git/about-git)
- [Creating a Codespace](https://docs.github.com/en/codespaces/developing-in-a-codespace/creating-a-codespace-for-a-repository)
- [Creating a PR from a fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork)
- [Resolving merge conflicts](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-using-the-command-line)
- [CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
