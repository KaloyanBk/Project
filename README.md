# Alien Invasion (C++ / SFML)

## EN

### Overview
`Alien Invasion` is a C++ arcade-style game project built with SFML for an Object-Oriented Programming course.  
The project focuses on OOP design, modular game architecture, and real-time gameplay logic.

### Main Features
- Single-player and two-player support
- Multiple enemy behaviors (including different movement/attack patterns)
- Weapon and bullet system
- Menu flow and in-game state switching
- Save/load game progress via JSON (`data/savedData.json`)

### Tech Stack
- C++11
- SFML (graphics, window, system, audio, network)
- nlohmann/json
- Makefile-based build

### Project Structure
- `src/` - implementation files
- `include/` - header files
- `data/` - saved game data
- `Fonts/` - font assets
- `makefile` - build and run commands

### Build & Run (macOS / Homebrew)
This project is currently configured for SFML installed via Homebrew on macOS.

1. Install dependencies:
   - `brew install sfml nlohmann-json`
2. Build:
   - `make`
3. Run:
   - `make run`
4. Clean:
   - `make clean`

### Controls
- **Player 1:** `W A S D` + `Space`
- **Player 2:** Arrow keys + `Right Shift`
- **Exit:** `Esc`

### Notes
- The `makefile` currently uses local Homebrew paths for SFML includes/libs.
- If your SFML path differs, update `CFLAGS` and `LDFLAGS` in `makefile`.

---

## BG

### Описание
`Alien Invasion` е аркаден проект на C++ със SFML, разработен като курсова задача по Обектно-ориентирано програмиране.  
Фокусът е върху ООП дизайн, модулна структура и реалновремева игрова логика.

### Основни функционалности
- Поддръжка на един и двама играчи
- Различни типове врагове и поведения
- Система за оръжия и куршуми
- Меню и управление на състоянията в играта
- Запис и зареждане на прогрес в JSON (`data/savedData.json`)

### Използвани технологии
- C++11
- SFML (graphics, window, system, audio, network)
- nlohmann/json
- Компилация чрез Makefile

### Структура на проекта
- `src/` - имплементация
- `include/` - header файлове
- `data/` - запазени данни
- `Fonts/` - шрифтове и ресурси
- `makefile` - команди за build и run

### Стартиране (macOS / Homebrew)
Проектът е конфигуриран за SFML, инсталиран чрез Homebrew на macOS.

1. Инсталиране на зависимости:
   - `brew install sfml nlohmann-json`
2. Компилация:
   - `make`
3. Стартиране:
   - `make run`
4. Почистване:
   - `make clean`

### Контроли
- **Играч 1:** `W A S D` + `Space`
- **Играч 2:** стрелки + `Right Shift`
- **Изход:** `Esc`

### Бележки
- `makefile` в момента използва локални Homebrew пътища за SFML.
- Ако SFML е на различен път, редактирай `CFLAGS` и `LDFLAGS` в `makefile`.
