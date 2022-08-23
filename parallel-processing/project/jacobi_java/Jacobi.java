import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
/**
 * This is the class that holds main and calls Grid methods from main local Grid instance "grid".
 * Jacobi requires 4 command-line arguments adhearing to the format of... 
 * [int,       int,                      double,          String          ]
 * [grid size, max number of iterations, error tolerance, output file name]
 *
 * @author Jordan Breen
 * @version 09/16/2021
 */
public class Jacobi {
    public static void main(String[] args) {
        // PARSING: ////////////////////////////////////////////////////////////////////////////////////////////////
        // This is the expected format of the command-line parameters, [int, int, double, String]
        Object[] parsedArgs = new Object[]{new Integer(0), new Integer(0), new Double(0), new String("")};
        int argc = parsedArgs.length;
        
        // Conditional Block: Checking for valid number of arguments
        if(args.length != argc) {
            System.err.println("Invalid command-line arguments, expecting " + argc + " arguments [int, int, double, String]");
            System.exit(1);
        }
        else {
            for(int i = 0; i < parsedArgs.length; i++) {
                try { 
                    // If the parameter calls for a(n)... store as specified type
                    // ...Integer
                    if(parsedArgs[i] instanceof Integer)
                        parsedArgs[i] = Integer.parseInt(args[i]); 
                    // ...Double
                    else if(parsedArgs[i] instanceof Double)
                        parsedArgs[i] = Double.parseDouble(args[i]); 
                    // ...Other, store as String
                    else
                        parsedArgs[i] = args[i];
                }
                catch(NumberFormatException ex) { 
                    System.err.println("Invalid argument for args[" + i + "]"); 
                    System.exit(1);
                }
            }
            // PROCESSING: /////////////////////////////////////////////////////////////////////////////////////////
            // Local Variables: of parsed command-line arguments, for clarity
            int    gridSize       = ((Integer)parsedArgs[0]).intValue();
            int    maxIterations  = ((Integer)parsedArgs[1]).intValue();
            double  errorTolerance = ((Double  )parsedArgs[2]).doubleValue();
            String outputFileName = ((String )parsedArgs[3]);
            String results;
            
            // Creation and populating of the Grid object:
            Grid grid = new Grid(gridSize);
            grid.fillGrid();
            
            // Begin the Jocobi step process send output to results String: 
            grid.process(maxIterations, errorTolerance);
            results = grid.toString(FormatMode.RESULT_VALUE);
            // OUTPUT: /////////////////////////////////////////////////////////////////////////////////////////////
            if(outputFileName == "-" || outputFileName == "") {
                System.out.println(results);
            }
            else {
                try {
                    FileWriter  FW = new FileWriter(outputFileName);
                    PrintWriter PW = new PrintWriter(FW);
                    PW.println(results);
                    PW.close();
                    FW.close();
                }
                catch(IOException ex) {
                    System.err.println("Error: IOException thrown in main, Cannot write to file <" + outputFileName + ">"); 
                    System.exit(1);
                }
            }
        }
    }
}
