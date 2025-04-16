```markdown
# Setting Up `icc` for Direct Command-Line Use

This guide shows how to configure the `icc` script so that you can run it directly from the terminal as:

```bash
icc input.ic
```

instead of:

```bash
sh icc input.ic
```

## Step 1: Make the Script Executable

Open your terminal and run:

```bash
chmod +x icc
```

## Step 2: Move the Script to a Directory in Your PATH

A good location is `~/.local/bin`, which is commonly used for user-specific executables.

```bash
mkdir -p ~/.local/bin
mv icc ~/.local/bin/
```

## Step 3: Add `~/.local/bin` to Your PATH (if not already)

### For Bash

Edit `~/.bashrc`:

```bash
nano ~/.bashrc
```

Add this line at the end:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Then apply the changes:

```bash
source ~/.bashrc
```

### For Zsh

Edit `~/.zshrc`:

```bash
nano ~/.zshrc
```

Add this line:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Then apply the changes:

```bash
source ~/.zshrc
```

## Step 4: Test It

Now you can run:

```bash
icc input.ic
```

from any directory, assuming `input.ic` is a valid Indent-C file.

---

## Optional: Verify PATH Includes `.local/bin`

Run:

```bash
echo $PATH | grep -q "$HOME/.local/bin" && echo "PATH is set correctly" || echo "PATH is missing ~/.local/bin"
```

If it's missing, repeat Step 3.

---
```