from openai import OpenAI
from datetime import date
import json

today = date.today()
today_str = today.strftime("%B %d, %Y")


client = OpenAI(
    api_key="undisclosed api key"
)

# 1. Read user command from transfer.txt
with open('transfer.txt', 'r') as f:
    user_command = f.read().strip()

# 2. Create a system prompt that instructs GPT to return structured data
system_prompt = (
    "You are a task manager assistant. "
    "Interpret the user's request and return the task details in this JSON format:\n\n"
    "{\n"
    "  \"operation\": \"create/remove/edit\",\n"
    "  \"task_number\": \"integer\",\n"
    "  \"title\": \"Task Title\",\n"
    "  \"description\": \"Task Description\",\n"
    "  \"date\": {\n"
    "    \"month\": \"MM\",\n"
    "    \"day\": \"DD\",\n"
    "    \"year\": \"YYYY\",\n"
    "    \"hour\": \"HH\",\n"
    "    \"minute\": \"MM\",\n"
    "    \"ampm\": \"AM/PM\"\n"
    "  }\n"
    "}\n"
    f"If date info is missing, or if the user's request mentions \'today\', use {today_str}"
    "If hour/minute info is missing, assume 11th hour, 59th minute, PM."
    "If any information is missing, leave that field as \"null\"."
)

completion = client.chat.completions.create(
    model="gpt-4o",
    messages=[
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_command}
    ]
)

try:
    # 4. Parse the JSON response
    ai_response = completion.choices[0].message.content.strip()
    task_data = json.loads(ai_response)

    operation = task_data.get("operation", "null").lower()
    task_number = str(task_data.get("task_number", "null"))
    task_title = task_data.get("title", "null")
    task_description = task_data.get("description", "null")

    # The "date" object is itself a dictionary
    date_info = task_data.get("date", {})
    month = date_info.get("month", "null")
    day = date_info.get("day", "null")
    year = date_info.get("year", "null")
    hour = date_info.get("hour", "null")
    minute = date_info.get("minute", "null")
    ampm = date_info.get("ampm", "null")

except Exception as e:
    operation = "null"
    task_number = "null"
    task_title = "null"
    task_description = "null"
    month = "null"
    day = "null"
    year = "null"
    hour = "null"
    minute = "null"
    ampm = "null"

# 5. Overwrite transfer.txt with the new output
with open('transfer.txt', 'w') as f:
    f.write(f"{operation}\n")        # 1: create/remove/edit
    f.write(f"{task_number}\n")      # 2: integer
    f.write(f"{task_title}\n")       # 3: task title
    f.write(f"{task_description}\n") # 4: task description
    f.write(f"{month}\n")            # 5: MM
    f.write(f"{day}\n")              # 6: DD
    f.write(f"{year}\n")             # 7: YYYY
    f.write(f"{hour}\n")             # 8: HH
    f.write(f"{minute}\n")           # 9: MM (minutes)
    f.write(f"{ampm}\n")             # 10: AM/PM
