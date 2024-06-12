package tutorial;

public class SWAR {
    private static final long MAGIC_MULTIPLIER = (100 * 0x1000000 + 10 * 0x10000 + 1);
    private static final long DOT_DETECTOR = 0x10101000;
    private static final long ASCII_TO_DIGIT_MASK = 0x0F000F0F00L;
    
    /**
     * Convert byte array to long value
     *
     * @param b
     *          The byte array to convert
     * @return The result of long
     */
    public static long byteArrayToLong(byte[] b) {
        long l = 0;
        for (int i = 0; i < b.length; i++) {
            l += (long) (b[b.length - i - 1] & 0xff) << (8 * i);
        }

        return l;
    }

    /**
     * At a high-level, the code code takes these steps:
     * 
     * <ul>
     * <li>Detect whether the number is negative (i.e., the first character is
     * -)</li>
     * <li>Zero out the sign character, if any</li>
     * <li>Find where is the decimal dot</li>
     * <li>Shift the contents so that the digits align with the template XY.Z placed
     * over the bits of the long value</li>
     * <li>Transform the ASCII characters to their digit values</li>
     * <li>Multiply each digit by its weight (1x, 10x, 100x), and add them all
     * up</li>
     * <li>Apply the sign</li>
     * </ul>
     * 
     * @param inputData
     * @return
     */
    static int parseDataPoint(long inputData) {
        //Detect whether the number is negative
        long negatedInput = ~inputData;
        long broadcastSign = (negatedInput << 59) >> 63;

        // Zero out the sign character, if any
        long maskToRemoveSign = ~(broadcastSign & 0xFF);
        long withSignRemoved = inputData & maskToRemoveSign;
        
        // Find where is the decimal dot
        int dotPos = Long.numberOfTrailingZeros(negatedInput & DOT_DETECTOR);
        long alignedToTemplate = withSignRemoved << (28 - dotPos);
        long digits = alignedToTemplate & ASCII_TO_DIGIT_MASK;
        long absValue = ((digits * MAGIC_MULTIPLIER) >>> 32) & 0x3FF;
        long temperature = (absValue ^ broadcastSign) - broadcastSign;
        long nextLineStart = (dotPos >>> 3) + 3;
        return (int) temperature;
    }

    public static void main(String args[]) {
        String temperature = "8.61-";

        System.out.println(parseDataPoint(byteArrayToLong(temperature.getBytes())));

        
    }
}