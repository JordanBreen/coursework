/**
   Solution to sum of primes finder, related to Goldbach's conjecture.

   The program takes a series of even integer values as its
   command-line parameters and for each one, finds the pair of primes
   that sum to that number, such that the smaller prime (if they
   differ) is as large as possible.  For example, for an input of 10,
   it can be expressed as 3+7 or 5+5.  5+5 will be reported as the
   answer, since the 5 is larger than 3.

   @author Jordan Breen
   @version Fall 2021
*/

public class Goldbach {

    // various class variables for inputs and times and results
    public static String mode;
    public static int numThreads;
    public static Thread threads[];
    public static BagOfNumbers bag;
    public static int n;
    public static long vals[];
    public static long launchTime;
    public static long startTimes[];
    public static long endTimes[];
    public static String results[];

    /**
       main method to run the experiment

       @param args the array of even input values to be used for the computation
    */
    public static void main(String args[]) {

    // baseline for timings (start of execution)
    launchTime = System.currentTimeMillis();
    
    if (args.length < 3) {
        System.err.println("Usage: java Goldbach numTheads mode [numbers]");
        System.exit(1);
    }

    
    n = args.length - 2;
    vals = new long[n];
    startTimes = new long[n];
    endTimes = new long[n];
    results = new String[n];

    numThreads = Integer.parseInt(args[0]);
    
    if (numThreads < 1) {
        System.err.println("Must specify at least one thread.");
        System.exit(1);
    }
    threads = new Thread[numThreads];

    mode = args[1];
    // check valid modes
    if(!mode.equals("interleaved") && !mode.equals("block") && !mode.equals("bag")) {
        System.err.println("Invalid threading mode " + mode);
        System.err.println("Must be one of block, interleaved, or bag.");
        System.exit(1);
    }
    
    if(mode.equals("bag")) {
        bag = new BagOfNumbers(0, n-1);
    }
    
    // get our numbers
    for (int i = 0; i < n; i++) {
        vals[i] = Long.parseLong(args[i+2]);
        // make sure all are even
        if (vals[i] % 2 == 1) {
        System.err.println("All numbers must be even! (found: " +
                   vals[i] + ")");
        System.exit(1);
        }
    }

    // start dealing with parallelism
    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = new WorkerThread(i)
        {
            @Override
            public void run()
            {
                doThreadWork(threadId);
            }
        };
        threads[i].start();
    }
    
    // out threads do work asynchronously
    
    for(int i = 0; i < numThreads; i++)
    {
        try
        {
            threads[i].join();
        }
        catch(InterruptedException e) {}
    }

    long totalTime = System.currentTimeMillis() - launchTime;
    
    // report times
    for (int i = 0; i < n; i++) {
        System.out.println("i = " + i + " (" + vals[i] + "=" + results[i] +
                   ") took " +
                   (endTimes[i] - startTimes[i]) + " ms from " +
                   (startTimes[i] - launchTime) + " to " +
                   (endTimes[i] - launchTime));
    }
    System.out.println("Total elapsed time: " + totalTime + " ms");
    }

    private static void doThreadWork(int threadId) {
        if(mode.equals("interleaved")) {
            for (int i = threadId; i < n; i+=numThreads) {
                startTimes[i] = System.currentTimeMillis();
                results[i] = findGoldbachPair(vals[i]);
                endTimes[i] = System.currentTimeMillis();
            }
        }
        else if(mode.equals("block")) {
            // compute the range of numbers this thread should work on
            int everyoneGets = n / numThreads;
            int leftovers = n % numThreads;
            int myStart = threadId * everyoneGets + Math.min(threadId, leftovers);
            int myCount = everyoneGets;
            if(threadId <= leftovers) myCount++;
            
            for (int i = threadId; i < n; i+=numThreads) {
                startTimes[i] = System.currentTimeMillis();
                results[i] = findGoldbachPair(vals[i]);
                endTimes[i] = System.currentTimeMillis();
            }
        }
        else { // mode is bag
            int nextIndex = 0;
            do {
                nextIndex = bag.next();
                if(nextIndex != -1) {
                    startTimes[nextIndex] = System.currentTimeMillis();
                    results[nextIndex] = findGoldbachPair(vals[nextIndex]);
                    endTimes[nextIndex] = System.currentTimeMillis();
                }
            } while(nextIndex != -1);
        }
    }
    
    /**
       Find and return (as a sum in String form) the pair of primes
       that sums to the given even positive value, such that the
       smaller of the primes (if they differ) is as large as possible.

       @param val the value for which to find the pair of primes
       @return a String representation of the addition of those primes
    */
    private static String findGoldbachPair(long val) {

    // special case of 4
    if (val == 4) return "2+2";

    // all others will be a sum of 2 odd primes
    long a = 3;
    // will be changed if conjecture is true
    String answer = "NO SOLUTION";
    while (a <= val/2) {
        if (isPrime(a) && isPrime(val-a)) answer = a + "+" + (val-a);
        a += 2;
    }

    return answer;
    }
    
    /**
       Check if the given value is prime.

       @param val the number to check
       @return true iff val is prime
    */
    private static boolean isPrime(long val) {

    if (val % 2 == 0) return false;
    long check = 3;
    long checkSq = check * check;
    while (checkSq <= val) {
        if (val % check == 0) return false;
        check += 2;
        checkSq = check * check;
    }
    return true;
    }
}

/* our WorkerThread, which just adds an instance variable
   and a constructor to set it to the Thread class. */
class WorkerThread extends Thread {

    protected int threadId;

    public WorkerThread(int threadId) {

    this.threadId = threadId;
    }
}

class BagOfNumbers {
    protected int nextVal;
    protected int lastVal;
    public BagOfNumbers(int start, int end) {
        nextVal = start;
        lastVal = end;
    }
    synchronized public int next() {
        if(nextVal > lastVal) return -1;
        int retVal = nextVal;
        nextVal++;
        return retVal;
    }
}