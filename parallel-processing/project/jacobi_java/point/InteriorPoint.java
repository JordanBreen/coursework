package point;
import java.util.Random;

/**
 * Class InteriorPoint - Subclass of Point, 
 * Represents a point enclosed by a collection of BoundaryPoints, these points
 * hold both a current value and their next value, the next value will be at -1
 * (indicated by setting to constant NOT_SET)
 * during most of the operating time throughout the program but will contain meaingful
 * data when it comes time to update the current value. Next value is determine by
 * the mean value of itself and its four Abstract point neighbors.
 *
 * @author Jordan Breen
 * @version 09/13/2021
 */
public class InteriorPoint extends AbstractPoint {
    private static final double NOT_SET = -1;
    private static final char   TOKEN   = '.';
    private static final Random RAND    = new Random();
    private double nextValue;
    
    public InteriorPoint() {
        super(TOKEN);
        nextValue = NOT_SET;
    }
    public void setValue() {
        super.setValue(RAND.nextFloat());
        nextValue = NOT_SET;
    }
    protected double getNextValue() {
        return this.nextValue;
    }
    public void setNextValue(AbstractPoint[] adjPoints) {
        nextValue = this.getAverage(adjPoints);
    }
    public void update() {
        super.setValue(nextValue);
        nextValue = NOT_SET;
    }
    private double getAverage(AbstractPoint[] adjPoints) {
        double average = this.getValue();
        for(int i = 0; i < adjPoints.length; i++)
            average += adjPoints[i].getValue();
        return average / (adjPoints.length + 1);
    }
    public double difference() {
        return Math.abs(nextValue - getValue());
    }
}
