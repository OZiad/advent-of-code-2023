import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import org.apache.commons.lang3.StringUtils;

public class App {
    public static void main(String[] args) throws Exception {
        String filePath = "input.txt";

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            int cumulativeSum = 0;
            int lineNumber = 0;
            while ((line = br.readLine()) != null) {
                Integer result = calibrationValue(line);

                if (result != null) {
                    System.out.println(
                            "Calibration value for line: number: " + ++lineNumber + "line: " + line + " is " + result);
                    cumulativeSum += result;
                    System.out.println("Total Sum is: " + cumulativeSum);
                } else {
                    System.out.println("No digits found in the line: " + line);
                }
            }
            System.out.println("Total Sum: " + cumulativeSum);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Method that replaces all numbers written in word form to corresponding
    // integers
    private static String replaceLetteredNumbers(String line) {
        String[] searchList = new String[] { "oneight", "twone", "eightwo", "one", "two", "three", "four", "five",
                "six", "seven", "eight", "nine" };
        String[] replacementList = new String[] { "18", "21", "82", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        return StringUtils.replaceEach(line, searchList, replacementList);
    }

    // Calculates sum of first and last numbers in a given string
    public static Integer calibrationValue(String line) {
        line = replaceLetteredNumbers(line);
        int left = 0;
        int right = line.length() - 1;
        while (left <= right) {
            if (!Character.isDigit(line.charAt(left))) {
                left++;
            }
            if (!Character.isDigit(line.charAt(right))) {
                right--;
            }
            if (left <= right && Character.isDigit(line.charAt(left)) && Character.isDigit(line.charAt(right))) {
                String result = line.charAt(left) + "" + line.charAt(right);
                return Integer.parseInt(result);
            }
        }

        return null;
    }
}
