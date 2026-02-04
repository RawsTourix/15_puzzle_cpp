## Сборка проекта (Visual Studio / MSBuild) через `.vcxproj`

### Через Visual Studio
1. Откройте файл проекта `*.vcxproj` (**Файл → Открыть → Проект/решение…**).
2. Visual Studio откроет проект и создаст решение «на лету». При необходимости сохраните его:
   - **Файл → Сохранить всё** → будет создан `*.sln` рядом с проектом.
3. Выберите конфигурацию (`Release`/`Debug`) и платформу (`x64`), затем выполните:
   - **Сборка → Собрать решение**).

### Через командную строку (MSBuild)
Откройте «Developer Command Prompt for VS» и выполните:

```bat
msbuild 15_puzzle.vcxproj /p:Configuration=Release /p:Platform=x64
```

Для Debug:

```bat
msbuild 15_puzzle.vcxproj /p:Configuration=Debug /p:Platform=x64
```