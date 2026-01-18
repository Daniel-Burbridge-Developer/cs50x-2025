import os
import random
import time
from io import BytesIO

import requests
from dotenv import load_dotenv
from google import genai


def main():
    load_dotenv()
    try:
        prompt, file_name = generate_prompt()
        generate_image(prompt, file_name)
    except Exception as e:
        print(f"An error occurred: {e}")
        generate_image()
    generate_image(prompt, file_name)


def generate_image(
    prompt="Cinematic shot of Baby Yoda (Grogu) wearing a knitted scarf, holding a cup of hot cocoa, autumn forest background, hyper-realistic, 8k, soft lighting, depth of field",
    file_name="todays_image",
):
    seed = random.randint(1, 1000000)
    url = f"https://image.pollinations.ai/prompt/{prompt}?width=1024&height=1024&seed={seed}&model=flux"

    print(f"Requesting Grogu from Pollinations (Seed: {seed})...")

    try:
        response = requests.get(url, timeout=30)
        if response.status_code == 200:
            # DIRECT WRITE (More robust than PIL for simple downloading)
            with open(file_name, "wb") as f:
                f.write(response.content)
            print(f"Success! Saved to {file_name}")
            return file_name
        else:
            print(f"Failed. Status Code: {response.status_code}")
            return None

    except Exception as e:
        print(f"Error: {e}")
        return None


def generate_prompt():
    client = genai.Client()

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents="Generate a prompt to create a unique grogu image come up with a random theme, location, item, scene, activity ONLY return the prompt and nothing else. For Nano Banana",
    )

    image_generate_prompt = response.text
    print(f"Image Prompt: {image_generate_prompt}")

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents=(
            f"Create a 2 word description of the image that would be generated from the follinw prompt. your response should be exactly 2 words in snake case: {image_generate_prompt}"
        ),
    )

    file_name = response.text.strip() + ".png"
    print(f"File Name: {file_name}")

    return image_generate_prompt, file_name


if __name__ == "__main__":
    main()
