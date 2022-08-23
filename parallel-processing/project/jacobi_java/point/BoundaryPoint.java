package point;
/**
 * Class BoundaryPoint - Subclass of Point
 * Represents a point that is a part of a zone of points that encloses all
 * InteriorPoint objects, contains a nested enum class that limits the range
 * of value to [1]U[0]. Unlike InteriorPoint, the value of BoundaryPoint does 
 * not change after its initial creation and setting in Grid.gridFill().
 *
 * @author Jordan Breen
 * @version 09/13/2021
 */
public class BoundaryPoint extends AbstractPoint {
    private static final char TOKEN = '*';
    private BoundaryPoint.Type type;
    public BoundaryPoint() {
        super(TOKEN);
        this.type = Type.fromValue(this.getValue());
    }
    public void setType(BoundaryPoint.Type type) {
        this.type = type;
        setValue(type.getValue());
    }
    public void setValue() {
        this.type = BoundaryPoint.Type.LOW;
        setValue(type.getValue());
    }
    public enum Type {
        HIGH(1.0f),
        LOW(0.0f);
        private final double value;
        private Type(double value) {
            this.value = value;
        }
        public double getValue() {
            return this.value;
        }
        public static Type fromValue(double value) {
            final double THRESHOLD = 0.001f;
            for(Type v: Type.values())
                if(value <= (v.value + THRESHOLD))
                    return v;
            return null;
        }
    }
}