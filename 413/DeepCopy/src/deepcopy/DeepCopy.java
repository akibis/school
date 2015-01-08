/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepcopy;

/**
 *
 * @author netdom
 */
public class DeepCopy {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        int[] a = {1, 2, 3, 4, 5, 6};
        int[] b = new int[a.length];
        
        System.out.println("******** A ********");
        for(int i = 0; i < a.length; i++){
            System.out.println(a[i]);
        }
        System.out.println("******** B ********");
        
        System.arraycopy(a, 0, b, 0, b.length);
        b[0] = 12;
        
        for(int i = 0; i < a.length; i++){
            System.out.println(b[i]);
        }        
        System.out.println("******* A *********");
        for(int i = 0; i < a.length; i++){
            System.out.println(a[i]);
        }
        System.out.println("****************");
    }
    
}
