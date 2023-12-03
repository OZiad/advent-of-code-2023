// https://adventofcode.com/2023/day/2
// 12 red cubes, 13 green cubes, and 14 blue cubes

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class App {
    public static void main(String[] args) throws Exception {
        String line;
        String filePath = "E:/Repos/advent-of-code-2023/AoC/day2/day2/input.txt";
        final int GAME_ID_INDEX = 8;
        int sum = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            while ((line = br.readLine()) != null) {
                int gameId = extractGameId(line);
                System.out.println("Line: " + line + " Game ID: " + gameId);
                line = line.substring(GAME_ID_INDEX);
                if (isValidGame(line, 12, 13, 14)) {
                    sum += gameId;
                    System.out.println("Valid Game, Total Sum: " + sum);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean isValidGame(String gameSet, int redCount, int greenCount, int blueCount) {
        String[] subsets = gameSet.split(";");

        // Use a list of sets in case of duplication
        List<Set<String>> gameSubsets = new ArrayList<>();

        // Add all cube counts to a the list of sets
        for (String subset : subsets) {
            // Remove any trailing colons
            subset = subset.replaceAll(":", "").trim();
            gameSubsets.add(new HashSet<>(List.of(subset.trim().split(", "))));
        }
        return isValidGameSet(gameSubsets, redCount, greenCount, blueCount);
    }

    // Receives all sets of cubes for a game
    private static boolean isValidGameSet(List<Set<String>> gameSubsets, int redCount, int greenCount, int blueCount) {
        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;
        for (Set<String> set : gameSubsets) {
            for (String cubes : set) {
                String[] parts = cubes.split(" ");
                int count = Integer.parseInt(parts[0]);
                String color = parts[1].toLowerCase();
                switch (color) {
                    case "red":
                        maxRed = Math.max(count, maxRed);
                        break;
                    case "green":
                        maxGreen = Math.max(count, maxGreen);
                        break;
                    case "blue":
                        maxBlue = Math.max(count, maxBlue);
                        break;
                    default:
                        return false;
                }
            }
        }

        return maxRed <= redCount && maxGreen <= greenCount && maxBlue <= blueCount;
    }

    private static int extractGameId(String line) {
        // String[] parts = line.split(":");
        int colonIndex = line.indexOf(":");
        return Integer.parseInt(line.substring(5, colonIndex).trim());
    }
}

/*
 * Logic:
 * Game 1: 4 red, 8 green; 8 green, 6 red; 13 red, 8 green; 2 blue, 4 red, 4
 * green
 * 
 * Split line by ';' -> [ "4 red, 8 green", "8 green, 6 red", "13 red, 8 green",
 * "2 blue, 4 red, 4 green" ]
 * 
 * loop through list of strings and split each string by "," and add to hash
 * set-> ["4 red", "8 green", "6 red", ... ]
 * 
 * for every set (game info) split strings in set by " " and use indices 0 and 1
 * to verify if game is viable
 * if viable -> extract game id to cumulative sum
 */
