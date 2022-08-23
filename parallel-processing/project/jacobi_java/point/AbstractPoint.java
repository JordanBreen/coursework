package point;
/**
 * Abstract class AbstractPoint - Superclass of BoundaryPoint and GridPoint, holds a token
 * and a double value. Only subclasses have access to manipulator methods (protected).
 *
 * @author Jordan Breen
 * @version 09/13/2021
 */
public abstract class AbstractPoint {
    // MEMBERS: //////////////////////////////////////////////////////
    private static final double DEFAULT_VALUE = 0.0f;
    private char   token; // a char representation, unique to subclass
    private double value; // a double value, where value = [0,1]
    // METHODS: //////////////////////////////////////////////////////
    // Constructor(s):
    protected AbstractPoint(char token) {
        this.token = token;
        this.value = DEFAULT_VALUE;
    }
    // Get(s) / Set(s):
    public char getToken() { 
        return token; 
    }
    protected double getValue() { 
        return value; 
    }
    protected void setValue(double value) { 
        this.value = value; 
    }
    protected abstract void setValue(); 
    // Formatting and Output:
    @Override
    public String toString() {
        return String.format("%1.3f", value);
    }
    public void print() {
        System.out.print(this.toString());
    }
}
