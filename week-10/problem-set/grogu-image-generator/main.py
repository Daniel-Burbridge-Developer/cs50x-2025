import os
import random
import time

import requests


def generate_grogu():
    # 1. The Prompt
    # We include "flux" in the URL to force the smart model
    prompt = "Cinematic shot of Baby Yoda (Grogu) wearing a knitted scarf, holding a cup of hot cocoa, autumn forest background, hyper-realistic, 8k, soft lighting, depth of field"

    # 2. The Random Seed
    # This ensures a new image every time.
    seed = random.randint(1, 1000000)

    # 3. The Magic URL
    # We pass 'model=flux' to get the high-quality AI
    url = f"https://image.pollinations.ai/prompt/{prompt}?width=1024&height=1024&seed={seed}&model=flux"

    print(f"Requesting Grogu from Pollinations (Seed: {seed})...")

    try:
        response = requests.get(url, timeout=30)

        if response.status_code == 200:
            # Save it to the current folder
            filename = "grogu_today.jpg"
            with open(filename, "wb") as f:
                f.write(response.content)
            print(f"Success! Saved to {filename}")
            return filename
        else:
            print(f"Failed. Status Code: {response.status_code}")
            return None

    except Exception as e:
        print(f"Error: {e}")
        return None


if __name__ == "__main__":
    generate_grogu()
