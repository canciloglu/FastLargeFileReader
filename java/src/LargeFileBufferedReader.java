/**
 *  Created on: Feb 21, 2016
 *      Author: Can Ciloglu 
 */
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class LargeFileBufferedReader {

	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		long lineCount = 0;
	    
		BufferedReader br = null;
		
		try {
			br = new BufferedReader(new FileReader("136mb.txt"));
			
			while (br.readLine() != null) {
				lineCount++;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if(br != null){
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}	
			}
		}
	    
	    long end = System.currentTimeMillis();
	    
	    System.out.println("Number of lines = " + lineCount + " processed in " + (end - start) + " ms");
	}

}
