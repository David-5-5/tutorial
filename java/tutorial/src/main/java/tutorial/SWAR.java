package tutorial;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;
import java.io.File;
import java.io.RandomAccessFile;
import java.lang.reflect.Field;
import java.net.URL;
import java.nio.channels.FileChannel.MapMode;

import sun.misc.Unsafe;

public class SWAR {
    /**
     * Transform a hex string to array byte
     *
     * @param s
     *          The hex string
     * @return The array byte
     * @throws IllegalBlockSizeException
     */
    public static final byte[] hexStringToBytes(String s) {

        if (s == null)
            return null;

        if (s.length() % 2 != 0) {
            String msg = String.format("The length of str[%s] should be even.", s);
            throw new RuntimeException(msg);
        }
        int temp[] = new int[s.length()];
        byte b[] = new byte[s.length() / 2];
        for (int i = 0; i < s.length(); i++) {
            temp[i] = Integer.parseInt(String.valueOf(s.charAt(i)), 16);
        }
        int k = 0;
        for (int j = 0; j < s.length(); j += 2) {
            b[k] = (byte) (temp[j] * 16 + temp[j + 1]);
            k++;
        }

        return b;
    }
    private static final Unsafe UNSAFE = unsafe();

    private static Unsafe unsafe() {
        try {
            ;
            Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
            theUnsafe.setAccessible(true);
            return (Unsafe) theUnsafe.get(Unsafe.class);
        } catch (NoSuchFieldException | IllegalAccessException e) {
            throw new RuntimeException(e);
        }

    }

    private static final long MAGIC_MULTIPLIER = (100 * 0x1000000 + 10 * 0x10000 + 1);
    private static final long DOT_DETECTOR = 0x10101000;
    private static final long ASCII_TO_DIGIT_MASK = 0x0F000F0F00L;


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
    static int parseDataPoint(long inputData, int dotPos) {
        // Detect whether the number is negative
        long negatedInput = ~inputData;
        long broadcastSign = (negatedInput << 59) >> 63;

        // Zero out the sign character, if any
        long maskToRemoveSign = ~(broadcastSign & 0xFF);
        long withSignRemoved = inputData & maskToRemoveSign;

        // Find where is the decimal dot

        long alignedToTemplate = withSignRemoved << (28 - dotPos);
        long digits = alignedToTemplate & ASCII_TO_DIGIT_MASK;
        long absValue = ((digits * MAGIC_MULTIPLIER) >>> 32) & 0x3FF;
        long temperature = (absValue ^ broadcastSign) - broadcastSign;
        long nextLineStart = (dotPos >>> 3) + 3;
        return (int) temperature;
    }

    private static final long BROADCAST_SEMICOLON = 0x3B3B3B3B3B3B3B3BL;
    private static final long BROADCAST_0x01 = 0x0101010101010101L;
    private static final long BROADCAST_0x80 = 0x8080808080808080L;

    private static long semicolonMatchBits(long word) {
        long diff = word ^ BROADCAST_SEMICOLON;
        return (diff - BROADCAST_0x01) & (~diff & BROADCAST_0x80);
    }

    // credit: artsiomkorzun
    private static long maskWord(long word, long matchBits) {
        long mask = matchBits ^ (matchBits - 1);
        return word & mask;
    }

    private static int nameLen(long separator) {
        return (Long.numberOfTrailingZeros(separator) >>> 3) + 1;
    }

    @SuppressWarnings("preview")
    public static void calculate() throws Exception {
        URL datafile = SWAR.class.getResource("measure.txt");
        File file = new File(datafile.getFile());

        try (RandomAccessFile in = new RandomAccessFile(file, "r")) {
            MemorySegment mapfile = in.getChannel().map(MapMode.READ_ONLY, 0, file.length(), Arena.global());
            long cursor = 0;
            long inputBase = mapfile.address();
            long inputSize = mapfile.byteSize();
            while (cursor < inputSize) {
                long nameStartOffset = cursor;
                int nameLen = 0;
                while (true) {
                    // 使用 unsafe 直接读取内存
                    long nameWord = UNSAFE.getLong(inputBase + nameStartOffset + nameLen);
                    // seek for semicolon ';'
                    long matchBits = semicolonMatchBits(nameWord);
                    if (matchBits != 0) {
                        // Find the ';'
                        nameLen += nameLen(matchBits);
                        nameWord = maskWord(nameWord, matchBits);
                        cursor += nameLen;
                        long tempWord = UNSAFE.getLong(inputBase + cursor);
                        System.out.println();
                        int dotPos = Long.numberOfTrailingZeros(~tempWord & DOT_DETECTOR);
                        int temperature = parseDataPoint(tempWord, dotPos);
                        System.out.println(String.format("Read hex string [%s], the string is [%s], and the temperature is [%d]", 
                        Long.toHexString(tempWord), new String(hexStringToBytes(Long.toHexString(tempWord))), temperature)); 
                        cursor += (dotPos >> 3) + 3;
                        break;
                    }
                    nameLen += Long.BYTES;
                }
            }
        }
    }

    public static void main(String args[]) throws Exception {
        calculate();
    }
}