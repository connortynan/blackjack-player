# Getting Started

Follow these steps to set up your own copy of this repository and personalize
it.

## 1. Fork this repository

1. In your browser, go to the GitHub page for this repo.
2. Click the **Fork** button (top-right).
3. Make sure the fork is created under **your** GitHub account.

## 2. Clone *your* fork

On your own machine, clone the fork you just created:

```bash
git clone https://github.com/<your-github-username>/blackjack-player.git
cd blackjack-player
```

Replace `<your-github-username>` with your actual GitHub username.

## 3. Rename the `player` directory with *your* name

You must rename the existing `player` directory to a directory with your own
name using `git mv player <your-name>`, so Git tracks the rename properly.

For example, if your name is Walter Goodzey, you would use:

```bash
git mv player walter-goodzey
```

Doing first name and last initial or github username is also fine (e.g., `walter-g`, `wimos-ai`).

### Guidelines

- Use all **lowercase**
- use **hyphens** instead of spaces (e.g., `walter-goodzey`)
- Do **not** delete and recreate the directory, use `git mv` to have a clean
version history

## Commit your change

```bash
git status    # Check that you made changes registered by git
git add .
git commit -m "Renamed player directory to my name"
```

## Push your changes to your fork

```bash
git push origin main
```
