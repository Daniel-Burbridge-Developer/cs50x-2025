import os
from discord import send_to_discord
from prompts import generate_prompt
from google import genai
from google.genai import types
import random
import requests
import time


CREATIVE_CONFIG = types.GenerateContentConfig(temperature=1.5)
HF_TOKEN = os.environ.get("HF_TOKEN")
OUTPUT_DIR = "./output"


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
    file_name="todays_image",
):
    timestamp = int(time.time())
    output_path = f"{OUTPUT_DIR}/{file_name}_{timestamp}.png"

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
