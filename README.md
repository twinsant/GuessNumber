# GuessNumber

**_A classic number guessing game for command line!_**

The program picks a random integer within a range, and you try to guess it within a limited number of attempts!

It supports custom ranges & attempt limits, logs game history, and writes logs for debugging.

## Dependencies

- C++17 compiler (`g++` 9+ or `clang++` 10+ is recommended)
- `GNU Make`
- `nlohmann/json.hpp` (already in `third_party/`)

### Install dependencies

**Ubuntu/Debian (Advanced Package Tool)**

```bash
sudo apt update
sudo apt install g++
sudo apt install make
```

**macOS (Homebrew)**

```bash
brew install gcc
brew install make
```

For other systems, use the equivalent package manager.

## Get the code

```bash
git clone https://github.com/AyineCode/GuessNumber.git
cd GuessNumber
```

## Install

From the project root, run:

```bash
make install
```

This will:
1. Build the release version
2. Install the binary to `~/.local/bin/guessnumber`
3. Create default configuration and history files in `~/.local/share/.guessnumber/`
4. Attempt to add `~/.local/bin` to your `PATH` (if it fails, it will show a manual instruction)

After installation, you can run `guessnumber` from anywhere.

## Basic usage

```bash
guessnumber [OPTIONS]
```

### Common options

| Option | Description |
|--------|-------------|
| `-h, --help` | Show help message |
| `-v, --version` | Show version |
| `-c, --config [min] [max] [attempts]` | Set game parameters (without arguments, show current config) |

**Examples**:

```bash
guessnumber -c 1 100 5   # range [1,100], max 5 attempts
guessnumber -c           # show current configuration
```

### Configuration file

Default location: `~/.local/share/.guessnumber/config.json`

Example:
```json
{
    "minNum": 1,
    "maxNum": 100,
    "attempts": 7
}
```

Game history is saved in `history.json` in the same directory.

## Uninstall

```bash
make uninstall          # remove only the binary
make uninstall-all      # remove binary and all user data (config, history)
```