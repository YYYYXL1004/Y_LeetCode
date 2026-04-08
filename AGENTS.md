# Repository Instructions

## Daily Summary Default Rules

When the user asks to summarize daily learning, update logs, or organize solved problems, always follow the workflow in [.cursor/skills/daily-summary/SKILL.md](.cursor/skills/daily-summary/SKILL.md).

## Required Consistency Checks

For each daily-summary update, all items below are mandatory:

1. Update daily log in daily/YYYY-MM.md.
2. Update README problem classification tables.
3. Update README monthly solved count.
4. Keep counts consistent:
   - README monthly increment = number of new entries added to daily log
   - README monthly increment = number of new entries added to README classification tables

## Scope of Count

Count includes new entries from these folders when they are included in summary/classification updates:
- LeetCode/
- TianTi/
- LanQiao/
- Learn/

This includes representative template entries (for example algorithm templates in Learn/) if they are added to daily log and README classification.

## Problem Summary Default Rules

When the user provides a problem statement and solution code and asks to "汇总" or "按这个格式整理", always follow the workflow in [.cursor/skills/problem-summary/SKILL.md](.cursor/skills/problem-summary/SKILL.md).

Output format in target cpp file must be:
1. Problem statement block comment at top.
2. Runnable solution code in the middle.
3. A concise `【总结】` section at bottom (model, correctness intuition, complexity, pitfalls).
