public enum Direction
{
    NORTH (0, Axis.VERTICAL  ),
    SOUTH (1, Axis.VERTICAL  ),
    EAST  (1, Axis.HORIZONTAL),
    WEST  (0, Axis.HORIZONTAL);
    
    private final int value;
    private final Axis axis;
    private Direction(int value, Axis axis)
    {
        this.value = value;
        this.axis  = axis;
    }
    public int getValue()
    {
        return this.value;
    }
    public Axis getAxis()
    {
        return this.axis;
    }
}