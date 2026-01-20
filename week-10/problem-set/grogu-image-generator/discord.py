import os
import requests

DISCORD_WEBHOOK_URL = os.environ["DISCORD_WEBHOOK_URL"]


def send_to_discord(image_path, prompt):
    try:
        with open(image_path, "rb") as f:
            files = {"file": (os.path.basename(image_path), f, "image/png")}
            data = {"content": f"🐸 **Today's Grogu**\n> {prompt[:1900]}"}
            response = requests.post(
                DISCORD_WEBHOOK_URL, data=data, files=files, timeout=30
            )

        if response.status_code in (200, 204):
            print("Successfully sent to Discord!")
        else:
            print(f"Discord webhook failed. Status: {response.status_code}")
    except Exception as e:
        print(f"Error sending to Discord: {e}")
