/**
 *  Created on: Feb 21, 2016
 *      Author: Can Ciloglu 
 */
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

public class LargeFileMappedBufferReader {

	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		long lineCount = 0;
		
	    FileChannel fc = null;
	    try {
	        fc = new RandomAccessFile("136mb.txt", "r").getChannel();
	        MappedByteBuffer mb = fc.map(FileChannel.MapMode.READ_ONLY, 0, fc.size());
	        while (mb.hasRemaining()) {
	            byte byteRead = mb.get();
	            if(byteRead == '\n') {
	            	lineCount++;
	            }
	        }
	    } catch (IOException e) {
	    	e.printStackTrace();
	    } finally {
	    	if(fc != null){
				try {
					fc.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
	    	}
		}
	    
	    long end = System.currentTimeMillis();
	    
	    System.out.println("Number of lines = " + lineCount + " processed in " + (end - start) + " ms");
	}

}
