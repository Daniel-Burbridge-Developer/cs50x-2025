from google.genai import genai, types

CREATIVE_CONFIG = types.GenerateContentConfig(temperature=1.5)


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
