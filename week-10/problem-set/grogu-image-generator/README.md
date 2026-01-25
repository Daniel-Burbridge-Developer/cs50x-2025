# 🐸 Grogu Image Generator

> CS50x Final Project — Daniel Burbridge

## 🎯 The Problem

My fiancée sends her boss a Baby Grogu meme every morning. I wanted to automate this little ritual and make her life a bit easier.

## 🔄 Scope Creep & Course Correction

**Original Vision:** A flexible, plugin-based image generation system with WhatsApp delivery, Docker deployment, configurable models, and a full CLI management interface.

**Reality Check:** After building the core functionality, I realized I was over-engineering a solution to a simple problem. The objective was never "build a flexible image platform" — it was "cute Baby Yodas, daily, to my fiancée's phone."

**What I Shipped:**

- ✅ Daily automated Grogu image generation
- ✅ AI-powered creative prompts (no two images alike)
- ✅ Discord delivery (easier than WhatsApp API)
- ✅ Fallback image providers for reliability
- ⏸️ Deferred: Docker deployment, WhatsApp integration, full CLI config

Sometimes the best engineering decision is knowing when to stop.

## 🛠️ Technical Stack

| Component          | Technology                                     |
| ------------------ | ---------------------------------------------- |
| Language           | Python 3.12                                    |
| Scheduling         | `schedule` library                             |
| Prompt Generation  | Gemini API                                     |
| Image Generation   | Pollinations (primary), HuggingFace (fallback) |
| Delivery           | Discord Webhook                                |
| Package Management | `uv`                                           |

## 📁 Project Structure

```
grogu-image-generator/
├── main.py           # Entry point, scheduler setup
├── image.py          # Image generation logic
├── prompts.py        # Gemini-powered prompt creation
├── discord.py        # Discord webhook delivery
├── cli.py            # Configuration CLI (partial)
├── config_manager.py # JSON config handler
├── config.json       # Model & schedule settings
└── output/           # Generated images
```

## 🚀 Usage

```bash
# Run the scheduler (runs continuously)
uv run main.py

# Or use the CLI for configuration
uv run cli.py
```

## 📊 Architecture

![System Architecture](docs/mermaid-diagram-v3.md)

## 📝 AI Disclosure

See [disclosure.txt](disclosure.txt) for details on AI-assisted portions of this project.

## 🎓 What I Learned

1. **Scope management** — It's easy to add features. It's hard to know when to stop.
2. **API integration** — Working with multiple external services (Gemini, Pollinations, HuggingFace, Discord).
3. **Error handling** — Building fallback systems for unreliable external services.
4. **The value of "good enough"** — A working simple solution beats an unfinished complex one.
