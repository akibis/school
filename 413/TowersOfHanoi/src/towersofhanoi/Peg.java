/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package towersofhanoi;
import java.util.Stack;
/**
 *
 * @author netdom
 * @param <Disk>
 */
public class Peg extends Stack<Disk>{

    private String pegName;
    
    public Peg(String name){
       pegName = name;
    }

    /**
     * @return the pegName
     */
    public String getPegName() {
        return pegName;
    }

    /**
     * @param pegName the pegName to set
     */
    public void setPegName(String pegName) {
        this.pegName = pegName;
    }
    
    public String printStack(int diskCount){
        String output = "";
        
        try{
        for (int i=0; i < this.size(); i++){
            output += get(i).getDiskNumber();
        }
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.print("empty");
        }
        return output;
    }
 

}
