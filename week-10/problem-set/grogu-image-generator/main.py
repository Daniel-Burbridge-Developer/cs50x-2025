import random
import os
from io import BytesIO
import requests
from dotenv import load_dotenv
from google import genai
from google.genai import types

import schedule
import time


load_dotenv()
# Adjusts predictability of LLM
CREATIVE_CONFIG = types.GenerateContentConfig(temperature=1.5)


DISCORD_WEBHOOK_URL = os.environ["DISCORD_WEBHOOK_URL"]
HF_TOKEN = os.environ.get("HF_TOKEN")
OUTPUT_DIR = "./output"


def main():
    print("starting up!")
    schedule.every(1).minute.do(report_idle)
    schedule.every(1).hour.do(report_wake_up)
    schedule.every().day.at("6:00").do(report_wake_up)

    while True:
        schedule.run_pending()
        time.sleep(1)


def report_idle():
    current_time = time.localtime
    print(f"Idling at: {current_time}")


def report_wake_up():
    current_time = time.localtime
    print(f"Ive been woken up to run my job! at: {current_time}")
    do_the_image_stuff()


def do_the_image_stuff():
    try:
        prompt, file_name = generate_prompt()
        image_path = generate_image(prompt, file_name)
        if image_path:
            send_to_discord(image_path, prompt)
    except Exception as e:
        print(f"An error occurred: {e}")
        image_path = generate_image()
        if image_path:
            send_to_discord(image_path, "prompt failed")


def generate_image(
    prompt="Cinematic shot of Baby Yoda (Grogu) wearing a knitted scarf, holding a cup of hot cocoa, autumn forest background, hyper-realistic, 8k, soft lighting, depth of field",
    file_name="todays_image.png",
):
    output_path = f"{OUTPUT_DIR}/{file_name}"

    # Try Pollinations first
    image_data = try_pollinations(prompt)

    # Fallback to HuggingFace if Pollinations fails
    if image_data is None and HF_TOKEN:
        print("Falling back to HuggingFace...")
        image_data = try_huggingface(prompt)

    if image_data:
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        with open(output_path, "wb") as f:
            f.write(image_data)
        print(f"Success! Saved to {output_path}")
        return output_path

    print("All image generation methods failed.")
    return None


def try_pollinations(prompt):
    seed = random.randint(1, 1000000)
    url = f"https://image.pollinations.ai/prompt/{prompt}?width=1024&height=1024&seed={seed}&model=flux"
    print(f"Requesting Grogu from Pollinations (Seed: {seed})...")

    try:
        response = requests.get(url, timeout=60)
        if response.status_code == 200:
            return response.content
        print(f"Pollinations failed. Status: {response.status_code}")
    except Exception as e:
        print(f"Pollinations error: {e}")
    return None


def try_huggingface(prompt):
    url = "https://api-inference.huggingface.co/models/stabilityai/stable-diffusion-xl-base-1.0"
    headers = {"Authorization": f"Bearer {HF_TOKEN}"}

    try:
        response = requests.post(
            url, headers=headers, json={"inputs": prompt}, timeout=120
        )
        if response.status_code == 200:
            return response.content
        print(f"HuggingFace failed. Status: {response.status_code}")
    except Exception as e:
        print(f"HuggingFace error: {e}")
    return None


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


def generate_prompt():
    client = genai.Client()

    # Step 1: Generate a completely random theme
    theme_response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents="Generate ONE unique, creative theme for an image. Be wildly creative - think unexpected combinations like 'baroque space opera', 'underwater jazz club', 'cottagecore apocalypse', 'neon noir ramen shop'. Return ONLY the theme, 2-4 words max.",
        config=CREATIVE_CONFIG,
    )
    theme = theme_response.text.strip()
    print(f"Random Theme: {theme}")

    # Step 2: Generate Grogu image prompt using that theme
    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents=f"Generate a prompt to create a unique Grogu (Baby Yoda) image with this theme: {theme}. Include specific details about location, lighting, items, and mood. ONLY return the prompt and nothing else.",
        config=CREATIVE_CONFIG,
    )

    image_generate_prompt = response.text
    print(f"Image Prompt: {image_generate_prompt}")

    # Step 3: Generate filename
    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents=f"Create a 2 word description of the image that would be generated from the following prompt. Your response should be exactly 2 words in snake_case: {image_generate_prompt}",
    )

    file_name = response.text.strip() + ".png"
    print(f"File Name: {file_name}")

    return image_generate_prompt, file_name


if __name__ == "__main__":
    main()
