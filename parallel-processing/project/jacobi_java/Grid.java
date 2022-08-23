import point.*;
/**
 * Write a description of class Grid here.
 *
 * @author Jordan Breen
 * @version 09/13/2021
 */
public class Grid
{
    private static final int BOUNDARY_THICKNESS = 1;
    private AbstractPoint[][] points;
    private int    size;
    private int    maxIter;
    private int    curIter;
    private long   timeElapsed;
    private double errorTolerance;
    private double maxDifference;
    public Grid(int size)
    {
        this.size        = size;
        this.curIter     = 0;
        this.timeElapsed = 0;
        this.points      = new AbstractPoint[this.getTotalSize()][this.getTotalSize()];
        initGrid();
    }
    /**
     * name: getTotalSize
     * purpose: returns the size of the entire grid (the Boundary and Interior)
     * @return the size of the grid, the length of the grid's side
     */ 
    private int getTotalSize()
    {
        return size + BOUNDARY_THICKNESS * 2;
    }
    /**
     * name: initGrid
     * 
     * purpose: Initializes the grid to its default values and appropriate AbstractPoint 
     * subclass, subclass choice is determined solely on positioning: 
     *  - BorderPoint objects on the borders
     *  - InteriorPoint objects on the inner grid
     *  - Below is an example of a Grid object of size 4;
     *  * * * * * *
     *  * . . . . *
     *  * . . . . *
     *  * . . . . *
     *  * . . . . *
     *  * * * * * *
     */
    private void initGrid()
    {
        for(int row = 0; row < getTotalSize(); row++)
            for(int col = 0; col < getTotalSize(); col++)
                if(isBoundaryZoning(row) || isBoundaryZoning(col))
                    points[col][row] = new BoundaryPoint();
                else
                    points[col][row] = new InteriorPoint();
    }
    /**
     * name: fillGrid
     * 
     * purpose: populates the grid with its starting values and using its default
     * border distribution. All of the InteriorPoint objects start at a random double
     * value [0,1] using the InteriorPoint.setValue() method, the BoundaryPoint objects
     * default to 1's in the top and left sides and 0's on the bottom and right (GRADIENT).
     * After this method finishes, the grid is ready to be put through Jacobi iterations.
     */ 
    public void fillGrid()
    {
        fillBoundary(Distribution.GRADIENT);
        int offset = BOUNDARY_THICKNESS;
        for(int row = offset; row < getTotalSize() - offset; row++)
            for(int col = offset; col < getTotalSize() - offset; col++)
                if(points[col][row] instanceof InteriorPoint)
                    ((InteriorPoint)points[col][row]).setValue();
    }
    /**
     * name: fillBoundary
     * 
     * purpose: to branch method calls depending on the Distribtion enum parameter.
     * Serves to simplify calls to fill the boundary of the grid and acts as a handler 
     * to fillGrid and both fillUniform and fillGradient
     * 
     * @param distribution the enum value that decides what method to call when filling the boundary
     */ 
    private void fillBoundary(Distribution distribution) {
        BoundaryPoint.Type DEFAULT_BPT = BoundaryPoint.Type.HIGH;
        Direction[]        DEFAULT_DIR = new Direction[]{Direction.NORTH, Direction.WEST};
        switch(distribution) {
            case GRADIENT : fillGradient(DEFAULT_DIR); break;
            case UNIFORM  : fillUniform(DEFAULT_BPT);  break;
            default       : break;
        }
    }
    /**
     * name: fillGradient
     * 
     * purpose: to fill the boundary of the grid in a non-uniform way, as specified by the Direction[]
     * parameter. The array argument is processed and the Directions passed indicate which areas of the
     * boundary are filled with HIGH(1) values. The Direction enums not listed are filled with LOW(0) values by
     * initially resetting the boundary to all zeros and masking over the desired areas with HIGH(1) values.
     * 
     * @param directions an array of directions, corelating to relative BoundaryPoint objects, to be filled with HIGH(1) values
     */ 
    private void fillGradient(Direction[] directions)
    {
        // Reset the boundary to all LOW(0)
        fillUniform(BoundaryPoint.Type.LOW);
        
        int minRow   = 0;
        int maxRow   = 0; 
        int minCol   = 0;
        int maxCol   = 0;
        int minIndex = 0;
        int maxIndex = this.getTotalSize() - 1;
        int limIndex = 0;
        for(int i = 0; i < directions.length; i++) {
            limIndex = maxIndex * (directions[i].getValue());
            switch(directions[i].getAxis()) {
                case HORIZONTAL:
                    // Full Range:
                    minRow = minIndex;
                    maxRow = maxIndex;
                    // Limited Range:
                    minCol = limIndex;
                    maxCol = limIndex;
                    break;
                case VERTICAL:
                    // Limited Range:
                    minRow = limIndex;
                    maxRow = limIndex;
                    // Full Range:
                    minCol = minIndex;
                    maxCol = maxIndex;
                    break;
            }
            for(int row = minRow; row <= maxRow; row++)
                for(int col = minCol; col <= maxCol; col++)
                    if(points[col][row] instanceof BoundaryPoint)
                        ((BoundaryPoint)points[col][row]).setType(BoundaryPoint.Type.HIGH);
        }
    }
    /**
     * name: fillUniform
     * 
     * purpose: to fill the boundary of the grid in a uniform way, all existing BoundaryPoint objects are
     * set to the BoundaryPoint.Type enum argument passed in. fillUniform(BoundaryPoint.Type.LOW) is a
     * reset of the grid's boundaries.
     * 
     * @param type the BoundaryPoint.Type the caller would like to be uniformly applied to the grid's boundary
     */ 
    private void fillUniform(BoundaryPoint.Type type)
    {
        for(int row = 0; row < getTotalSize(); row++)
            for(int col = 0; col < getTotalSize(); col++)
                if(points[col][row] instanceof BoundaryPoint)
                    ((BoundaryPoint)points[col][row]).setType(type);
    }
    /**
     * name: isBoundaryZoning
     * 
     * purpose: to see if the current index argument is within a zone reserved to hold BoundaryPoint
     * objects. This is used before either BoundaryPoint objects or InternalPoint objects are initialized
     * on the grid. The grid does not know where the boundary should be otherwise as it is just expected
     * to hold any instances of AbstractPoint objects
     * 
     * @param index the current index relative to either the current row or column of the 2D grid
     * @return a boolean stating if the index is in a zone to be filled with BoundaryPoint objects
     */ 
    private boolean isBoundaryZoning(int index) {
        return (index == 0 || index == getTotalSize()-1);
    }
    /**
     * name: isInteriorZoning
     * 
     * purpose: the inverse of the isBoundaryZoining method above, added for self-documentation in method calls.
     * 
     * @param index the current index relative to either the current row or column of the 2D grid
     * @return a boolean stating if the index is in a zone to be filled with InteriorPoint objects
     */ 
    private boolean isInteriorZoning(int index) {
        return !isBoundaryZoning(index);
    }
    /**
     * name: process
     * 
     * purpose: to call the iterate method until one of the conditions provided by the arguments are met
     *      - the method iterate has executed maxIter times, this is sourced from a command-line argument from
     *        the user on the start of the program
     *      - none of the differences between new and current InteriorPoint object values exceed the user-set
     *        error tolerance threshold, this signifies an end to any meaningful change in the values between
     *        iterations, this is another variable sourced from the user as a command-line argument to main
     * when either condition is met, the time in milliseconds is captured and saved in its respective class
     * member "timeElapsed", this will be used later in a record stating some statistics about the call to process().
     * 
     * @param maxIter the maximum number of times method iterate can execute
     * @param errorTolerance the minimum amount of difference at least one InteriorPoint object must satisfy to continue
     */ 
    public void process(int maxIter, double errorTolerance) {
        long startTime, endTime;
        this.maxIter = maxIter;
        this.errorTolerance = errorTolerance;
        startTime = System.currentTimeMillis();
        while(iterate() && curIter < maxIter);
        endTime = System.currentTimeMillis();
        this.timeElapsed = endTime - startTime;
    }
    /**
     * name: iterate
     * 
     * purpose: to visit each InteriorPoint object on the 2D grid, grab its four adjacent AbstractPoint
     * neighbors, find the mean value between them and the current value, and save it as the next value.
     * Once all of the new values have been calculated, all of the InteriorPoint objects are updated to
     * their new values, and newValue is reset
     * 
     * @return a boolean stating if at least one of the InteriorPoint object's value difference has exceeded the error tolerance threshold.
     */ 
    private boolean iterate() {
        this.maxDifference = 0;
        int offset = BOUNDARY_THICKNESS;
        InteriorPoint IP;
        // for each InteriorPoint object in grid
        for(int row = offset; row < getTotalSize() - offset; row++) {
            for(int col = offset; col < getTotalSize() - offset; col++) {
                IP = (InteriorPoint)points[col][row];        // cast AbstractPoint object to an InteriorPoint object
                IP.setNextValue(getAdjacentPoints(col,row)); // grab all four adjacent AbstractPoint objects
                testMaxDifference(IP);                       // test current difference against previous maxDifference
            }
        }
        // for each InteriorPoint object in grid
        for(int row = offset; row < getTotalSize() - offset; row++) {
            for(int col = offset; col < getTotalSize() - offset; col++) {
                IP = (InteriorPoint)points[col][row];   // cast AbstractPoint object to an InteriorPoint object
                IP.update();                            // update each InteriorPoint value to its nextValue
            }
        }
        // update termination-condition variables
        curIter++;
        return isAboveErrorTolerance();
    }
    /**
     * name: testMaxDifference
     * 
     * purpose: to test each current InteriorPoint objects' difference against the previous maxDifference.
     * This method seeks to find the highest difference in values for each individual call of method iterate(), 
     * as the previous maxDifference is clear at the beginning of each call to method iterate().
     * 
     * @param point the current point that method iterate is using, assumed to already have nextValue calculated
     */
    private void testMaxDifference(InteriorPoint point) {
        double curDifference = point.difference();
        maxDifference = (curDifference > maxDifference ? curDifference : maxDifference);
    }
    /**
     * name: isAboveErrorTolerance
     * 
     * purpose: to test if the max difference found by testMaxDifference difference exceeds the minimum difference 
     * specified by the user. If all InteriorPoint objects fail this test then the processing of the grid is 
     * complete, otherwise the method iterate is fine to coninue processing the grid.
     * 
     * @return a boolean value stating if the max difference of the current iterate cycle, exceeds the error tolerance threshold
     */
    private boolean isAboveErrorTolerance() {
        return maxDifference >= errorTolerance;
    }
    /**
     * name: getAdjacentPoints
     * 
     * purpose: to return the four adjacent AbstractPoints in the grid relative to the column and row provided by 
     * the argument. The 4 are selected purely by proximity and does not discriminate between BoundaryPoint objects
     * and InteriorPoint objects, since these values are being collected only to retrieve their values via method
     * AbstractPoint.getValues().
     * 
     * @param inCol the column of the relevant InteriorPoint object
     * @param inRow the row of the relevant InteriorPoint object
     * @return an array of the adjacent BoundaryPoint and or InteriorPoint objects
     */
    private AbstractPoint[] getAdjacentPoints(int inCol, int inRow) {
        AbstractPoint[] outPoints = null;
        if(points[inCol][inRow] instanceof InteriorPoint) {
            final int SAMPLE_SIZE = 4;
            outPoints = new AbstractPoint[SAMPLE_SIZE];  // Make space for 4 points
            outPoints[0] = points[inCol + 1][inRow + 0]; // Right
            outPoints[1] = points[inCol - 1][inRow + 0]; // Left
            outPoints[2] = points[inCol + 0][inRow + 1]; // Down
            outPoints[3] = points[inCol + 0][inRow - 1]; // Up
        }
        return outPoints;
    }
    /**
     * name: getAdjacentPoints
     * 
     * purpose: function overload of toString(), returns a formatted string relating to the FormatMode
     * argument passed in.
     *      TOKEN:        a character representation of the grid, distinguished by the tokens of BoundaryPoint and 
     *                    InteriorPoint.
     *      TOKEN_VALUE:  as a call to TOKEN for InteriorPoint objects, but a integer truncated form of the value in 
     *                    BoundaryPoint objects.
     *      VALUE:        a double representation of the grid, displays the values of all BoundaryPoint and InteriorPoint 
     *                    objects.
     *      RESULT:       a String of some statistics about the execution of method process, such as number of iterations, 
     *                    the most recent maximum difference, and time elapsed.
     *      RESULT_VALUE: as a call to RESULT and VALUE, in that order.
     * 
     * @param FM the chosen formatting option for the returned String
     * @return a formatted String determined by argument FM
     */
    public String toString(FormatMode FM) {
        String output = "";
        switch(FM)
        {
            case TOKEN:
                for(int row = 0; row < getTotalSize(); row++) {
                    for(int col = 0; col < getTotalSize(); col++) {
                        output += points[col][row].getToken() + " ";
                    } output += "\n";
                }
                break;
            case TOKEN_VALUE:
                for(int row = 0; row < getTotalSize(); row++) {
                    for(int col = 0; col < getTotalSize(); col++) {
                        if(points[col][row] instanceof InteriorPoint)
                            output += points[col][row].getToken() + " ";
                        else
                            output += points[col][row].toString().substring(0,1) + " ";
                    } output += "\n";
                }
                break;
            case VALUE:
                for(int row = 0; row < getTotalSize(); row++) {
                    for(int col = 0; col < getTotalSize(); col++) {
                        output += points[col][row].toString() + " ";
                    } output += "\n";
                }
                break;
            case RESULT:
                output = getResultsString();
                break;
            case RESULT_VALUE:
                output = toString(FormatMode.RESULT) + "\n" + toString(FormatMode.VALUE);
                break;
        }
        return output;
    }
    /**
     * name: getAdjacentPoints
     * 
     * purpose: returns a String containing some statistics about the execution of method process, is called by
     * Grid.toString(FormatMode.RESULT), and consequentially Grid.toString(FormatMode.RESULT_VALUE).
     * 
     * @return a String containing some statistics about the execution of method process
     */
    private String getResultsString() {
        return "Completed "    + curIter       + " iteration pairs, " + 
               "last maxDiff " + maxDifference + ", "                 + 
               ""              + timeElapsed   + " ms";
    }
}
