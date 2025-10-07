#!/usr/bin/env python3

import numpy as np
from collections import Counter, defaultdict
from pathlib import Path
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap

def read_trace(file_path: str = "trace.log") -> list[str]:
    if not Path(file_path).is_file():
        raise FileNotFoundError(f"Файл {file_path} не найден.")
    with open(file_path, 'r', encoding='utf-8') as f:
        return [line.strip() for line in f if line.strip()]

def get_log_events(lines: list[str]) -> list[str]:
    """Возвращает все строки вида 'op <- op' как события."""
    events = []
    for line in lines:
        if " <- " in line:
            parts = line.split(" <- ", 1)
            if len(parts) == 2 and parts[0] and parts[1]:
                events.append(line)
    return events

def find_all_patterns(events: list[str], max_len: int = 5) -> dict[int, list[tuple[str, int]]]:
    """Находит все паттерны (не только топ) для каждой длины."""
    results = {}
    for length in range(1, max_len + 1):
        pattern_counts = Counter()
        for i in range(len(events) - length + 1):
            pattern = "\n".join(events[i:i + length])
            pattern_counts[pattern] += 1
        results[length] = pattern_counts.most_common()
    return results

def get_all_rotations(pattern: str) -> list[str]:
    """Возвращает все циклические сдвиги паттерна."""
    events = pattern.split('\n')
    n = len(events)
    rotations = []
    for i in range(n):
        rotated = events[i:] + events[:i]
        rotations.append("\n".join(rotated))
    return rotations

def merge_cyclic_patterns(patterns_by_len: dict[int, list[tuple[str, int]]]) -> dict[int, list[tuple[str, int]]]:
    """Объединяет циклически эквивалентные паттерны, оставляя топового представителя."""
    merged_results = {}
    
    for length, patterns in patterns_by_len.items():
        pattern_groups = defaultdict(list)
        for pattern, count in patterns:
            rotations = get_all_rotations(pattern)
            canonical = min(rotations)
            pattern_groups[canonical].append((pattern, count))
        
        merged_patterns = []
        for canonical, group in pattern_groups.items():
            top_pattern, top_count = max(group, key=lambda x: x[1])
            merged_patterns.append((top_pattern, top_count))
        
        merged_patterns.sort(key=lambda x: x[1], reverse=True)
        merged_results[length] = merged_patterns
    
    return merged_results

def get_top_patterns(merged_patterns: dict[int, list[tuple[str, int]]], top_k: int = 10) -> dict[int, list[tuple[str, int]]]:
    """Выбирает топ-K паттернов для каждой длины."""
    top_results = {}
    for length, patterns in merged_patterns.items():
        top_results[length] = patterns[:top_k]
    return top_results

def plot_top_patterns(top_patterns: dict[int, list[tuple[str, int]]], output_dir: str = "statistics"):
    """Строит графики для топ-10 паттернов в красивом стиле."""
    Path(output_dir).mkdir(exist_ok=True)
    violet_to_green = LinearSegmentedColormap.from_list("violet_to_green", ["#8A2BE2", "#32CD32"])

    for length, patterns in top_patterns.items():
        if not patterns:
            continue

        labels, counts = zip(*patterns)
        counts = list(counts)
        n = len(counts)
        colors = violet_to_green(np.linspace(0, 1, n))

        fig_width = max(10, n * 1.8)
        fig, ax = plt.subplots(figsize=(fig_width, 6))

        bar_width = 0.6
        x_positions = range(n)
        bars = ax.bar(x_positions, counts, color=colors, width=bar_width)

        ax.set_title(f"Топ-{n} паттернов длины {length}", fontsize=14, weight='bold')
        ax.set_ylabel("Частота", fontsize=12)
        ax.set_xticks(x_positions)
        ax.set_xticklabels(labels, rotation=0, fontsize=9, ha='center')

        for bar, count in zip(bars, counts):
            ax.text(bar.get_x() + bar.get_width() / 2,
                    bar.get_height() + max(counts) * 0.01,
                    str(count), 
                    ha='center', va='bottom', fontsize=9, weight='bold')

        plt.tight_layout(pad=3.0)
        plt.savefig(f"{output_dir}/patterns_len_{length}.png", dpi=150)
        plt.close(fig)

def save_top_patterns_to_file(top_patterns: dict[int, list[tuple[str, int]]], output_dir: str = "statistics"):
    """Сохраняет топ-10 паттернов в текстовый файл в указанной папке."""
    output_file = Path(output_dir) / "top_patterns.txt"
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write("=" * 50 + "\n")
        f.write("ТОП-10 ПАТТЕРНОВ (ЦИКЛИЧЕСКИЕ СДВИГИ ОБЪЕДИНЕНЫ)\n")
        f.write("=" * 50 + "\n\n")
        
        for length in sorted(top_patterns.keys()):
            patterns = top_patterns[length]
            if patterns:
                f.write(f"ТОП-10 ПАТТЕРНОВ ДЛИНЫ {length}:\n")
                f.write("-" * 40 + "\n")
                
                for i, (pattern, count) in enumerate(patterns, 1):
                    f.write(f"{i:2d}. Частота: {count:>6}\n")
                    lines = pattern.split('\n')
                    for line in lines:
                        f.write(f"     {line}\n")
                    f.write("\n")
                
                f.write("\n")

def main():
    lines = read_trace()
    events = get_log_events(lines)
    print(f"Загружено {len(events)} событий зависимости.")
    
    print("Поиск всех паттернов...")
    all_patterns = find_all_patterns(events, max_len=5)
    
    print("Объединение циклически эквивалентных паттернов...")
    merged_patterns = merge_cyclic_patterns(all_patterns)
    
    print("Выбор топ-10 паттернов для каждой длины...")
    top_patterns = get_top_patterns(merged_patterns, top_k=10)
    
    print("Создание графиков для топ-10 паттернов...")
    plot_top_patterns(top_patterns, output_dir="smart_statistics")
    
    print("Сохранение топ-10 паттернов в файл...")
    save_top_patterns_to_file(top_patterns, output_dir="smart_statistics")
    
    print(f"\nФИНАЛЬНЫЕ РЕЗУЛЬТАТЫ СОХРАНЕНЫ:")
    print(f"  - Графики: в папке './smart_statistics/'")
    print(f"  - Список паттернов: './smart_statistics/top_patterns.txt'")

if __name__ == "__main__":
    main()
    