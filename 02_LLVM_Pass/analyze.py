#!/usr/bin/env python3

import numpy as np
from collections import Counter
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

def find_frequent_patterns(events: list[str], max_len: int = 5, top_k: int = 10) -> dict[int, list[tuple[str, int]]]:
    results = {}
    for length in range(1, max_len + 1):
        pattern_counts = Counter()
        for i in range(len(events) - length + 1):
            pattern = "\n".join(events[i:i + length])
            pattern_counts[pattern] += 1
        results[length] = pattern_counts.most_common(top_k)
    return results

def plot_patterns(patterns_by_len: dict[int, list[tuple[str, int]]], output_dir: str = "statistics"):
    Path(output_dir).mkdir(exist_ok=True)
    violet_to_green = LinearSegmentedColormap.from_list("violet_to_green", ["#8A2BE2", "#32CD32"])

    for length, top_patterns in patterns_by_len.items():
        if not top_patterns:
            continue

        labels, counts = zip(*top_patterns)
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

        # Все числа строго по центру колонок
        for bar, count in zip(bars, counts):
            ax.text(bar.get_x() + bar.get_width() / 2,  # Строго центр колонки
                    bar.get_height() + max(counts) * 0.01,
                    str(count), 
                    ha='center',  # Горизонтальное выравнивание по центру
                    va='bottom',  # Вертикальное выравнивание снизу
                    fontsize=9,
                    weight='bold')

        plt.tight_layout(pad=3.0)
        plt.savefig(f"{output_dir}/patterns_len_{length}.png", dpi=150)
        plt.close(fig)

def main():
    lines = read_trace()
    events = get_log_events(lines)
    print(f"Загружено {len(events)} событий зависимости.")
    patterns = find_frequent_patterns(events, max_len=5, top_k=10)
    plot_patterns(patterns)
    print("Графики сохранены в './statistics/'")

if __name__ == "__main__":
    main()
