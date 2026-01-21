import json
import os

CONFIG_FILE = "config.json"


class ConfigManager:
    def __init__(self, config_file=CONFIG_FILE):
        self.config_file = config_file
        self.config = self._load_config()

    def _load_config(self):
        if not os.path.exists(self.config_file):
            return {"models": {}, "options": {}, "schedule": {}}
        try:
            with open(self.config_file, "r") as f:
                return json.load(f)
        except json.JSONDecodeError:
            return {"models": {}, "options": {}, "schedule": {}}

    def save(self):
        with open(self.config_file, "w") as f:
            json.dump(self.config, f, indent=4)

    def get_models(self):
        return self.config.get("models", {})

    def add_model(self, name, alias, preference, call_method, token):
        if name in self.config.get("models", {}):
            return False, "Model already exists"

        if "models" not in self.config:
            self.config["models"] = {}

        self.config["models"][name] = {
            "alias": alias,
            "preference": int(preference),
            "call_method": call_method,
            "Token": token,
        }
        self.save()
        return True, "Model added successfully"

    def get_options(self):
        return self.config.get("options", {})

    def get_schedule(self):
        return self.config.get("schedule", {})

    def update_preference(self, model_alias, new_preference):
        # Find model by alias
        target_model = None
        swap_model = None
        for name, data in self.config.get("models", {}).items():
            if data.get("alias") == model_alias:
                target_model = name
                break

        if not target_model:
            return False, "Model not found"

        for name, data in self.config.get("models", {}).items():
            if data.get("preference") == int(new_preference):
                swap_model = name
                break

        old_preference = self.config["models"][target_model]["preference"]
        self.config["models"][target_model]["preference"] = int(new_preference)
        self.config["models"][swap_model]["preference"] = int(old_preference)

        self.save()
        return True, "Preference updated"
