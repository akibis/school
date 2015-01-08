/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package towersofhanoi;

/**
 *
 * @author netdom
 */
public class Disk{
    final private String diskName;
    final private int diskNumber;
    
    public Disk(int number){
        diskName = "Disk " + number;
        diskNumber = number;
    }
    
    /**
     * @return the diskName
     */
    public String getDiskName() {
        return diskName;
    }

    /**
     * @return the diskNumber
     */
    public int getDiskNumber() {
        return diskNumber;
    }

}
