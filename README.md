# Clipject - Social Media Downloader Discord Bot

A Discord bot built with [D++](https://github.com/brainboxdotcc/DPP) that downloads and injects media content from popular social platforms directly into your Discord server. Powered by [Cobalt API](https://github.com/imputnet/cobalt) for reliable media extraction.

## Features

- 🎥 Download videos and media from multiple platforms:
  - Instagram (posts, reels, IGTV)
  - TikTok (videos and short links)
  - Facebook (videos, reels, watch links)
- 📤 Automatic upload to Discord channels
- ⚡ Fast processing with real-time status updates
- 🔒 Ephemeral command responses for privacy
- 🗑️ Automatic cleanup of temporary files
- 🏗️ Modular architecture with separation of concerns

## Prerequisites

- **Visual Studio 2022** (with C++ development tools)
- **Windows 10** (x64 or x86)
- **Cobalt API Instance** (self-hosted or remote)
- **Discord Bot Token** from [Discord Developer Portal](https://discord.com/developers/applications)

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/clipject.git
cd clipject
```

### 2. Set Up Cobalt API

Follow the [Cobalt self-hosting guide](https://github.com/imputnet/cobalt/blob/main/docs/run-an-instance.md) to run your own instance.

**Quick setup with Docker:**
```bash
docker run -p 9000:9000 ghcr.io/imputnet/cobalt:latest
```

**Or configure .env file:**
```env
API_URL="http://localhost:9000/"
API_PORT=9000
```

### 3. Configure the Bot

Open `src/Config.cpp` and update:
```cpp
const std::string BOT_TOKEN = "YOUR_DISCORD_BOT_TOKEN_HERE";
const std::string COBALT_API = "http://localhost:9000/"; // Your Cobalt instance URL
const bool KEEP_DOWNLOADED_FILES = false; // Set to true to keep downloaded files
const std::string DOWNLOAD_DIR = "./downloads/"; // Download directory
```

### 4. Build the Project

1. Open `MyBot.sln` in Visual Studio 2022
2. Select your configuration (Debug/Release, x64/x86)
3. Press `F7` or **Build** → **Build Solution**
4. The executable will be in `x64/Debug/` or `x64/Release/`

## Usage

### Starting the Bot

1. Run the compiled executable
2. Wait for the "Bot is ready!" message
3. Invite the bot to your Discord server with the appropriate permissions

### Discord Commands

#### `/inject`
Downloads and posts media from social platforms.

**Parameters:**
- `link` (required) - URL from Instagram, TikTok, or Facebook

**Example:**
```
/inject link: https://www.instagram.com/reel/ABC123/
/inject link: https://www.tiktok.com/@user/video/1234567890
/inject link: https://www.facebook.com/share/r/ABC123/
```

**Response Flow:**
1. 🔍 Validating link...
2. 📥 Downloading media from API...
3. 💾 Downloading file...
4. 📤 Uploading to Discord...
5. ✅ Media injected successfully!

## Supported Platforms

| Platform | Supported Formats |
|----------|------------------|
| **Instagram** | Posts, Reels, IGTV |
| **TikTok** | Videos, Short links (vm.tiktok.com, vt.tiktok.com) |
| **Facebook** | Videos, Reels, Watch, Share links |
| **YouTube** | ⚠️ Currently disabled |

## Dependencies

- **[D++ (DPP)](https://github.com/brainboxdotcc/DPP)** - Discord API library
- **[libcurl](https://curl.se/libcurl/)** - HTTP client for API requests and downloads
- **[JsonCpp](https://github.com/open-source-parsers/jsoncpp)** - JSON parsing
- **[Cobalt API](https://github.com/imputnet/cobalt)** - Media extraction service

## Troubleshooting

### "Failed to parse API response"
- Ensure Cobalt API is running and accessible
- Check `COBALT_API` URL in Config.cpp
- Verify network connectivity

### "Invalid link!"
- Confirm the URL matches supported format
- Check regex patterns in `LinkValidator.cpp`

### "Failed to download the media file"
- Cobalt API may not support the specific content
- Platform may have restrictions
- Check Cobalt API logs

### Bot doesn't respond
- Verify bot token is correct
- Check bot has necessary Discord permissions
- Ensure slash commands are registered (wait ~1 hour after first run)

## Required Discord Permissions

- `applications.commands` - Use slash commands
- `bot` - Basic bot functionality
- Send Messages
- Attach Files
- Use Slash Commands

**Bot Invite URL:**
```
https://discord.com/api/oauth2/authorize?client_id=YOUR_CLIENT_ID&permissions=274878024768&scope=bot%20applications.commands
```

## License

This project is licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0)**.

This means:
- ✅ You can use, modify, and distribute this software
- ✅ You must disclose the source code of any modifications
- ✅ You must license derivative works under AGPL-3.0
- ✅ **If you run a modified version on a server, you must make the source available to users**

See the [LICENSE](LICENSE) file for full details, or visit [https://www.gnu.org/licenses/agpl-3.0.en.html](https://www.gnu.org/licenses/agpl-3.0.en.html)

**Note:** This project is based on the [D++ Windows Bot Template](https://github.com/brainboxdotcc/windows-bot-template) which was originally licensed under Apache 2.0. The modifications and additions in this project are licensed under AGPL-3.0.

## Acknowledgments

- [D++ Discord Library](https://github.com/brainboxdotcc/DPP) by brainboxdotcc
- [Cobalt API](https://github.com/imputnet/cobalt) by imputnet

---
