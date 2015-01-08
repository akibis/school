/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package towersofhanoi;
import java.util.Scanner;
import java.util.*;
/**
 *
 * @author netdom
 */
public class TowersOfHanoi {
            
       static Peg A = new Peg("A");
       static Peg B = new Peg("B");        
       static Peg C = new Peg("C");
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("Welcome to Towers of Hanoi!");
        System.out.println("By: Aleksandr Kibis\n\n");
        System.out.print("Please enter number of disks: ");
        Scanner input = new Scanner(System.in);
        int diskNum = input.nextInt();
        playGame(diskNum);
    }
    
    public static void playGame(int numberOfDisks){

             
        for (int i=numberOfDisks; i > 0; i--){
            A.push(new Disk(i));
        }
        System.out.println("Move\t\t\t\t\tPeg Configuration");
        System.out.println("    \t\t\tA\t\t\tB\t\t\tC");
        System.out.println("init\t\t\t" + A.printStack(A.size()));
        sortTowers(numberOfDisks, A, B, C);
        
    }
    public static void printTowers(int diskCount, Peg A, Peg B, Peg C){
        System.out.print("Disk " + diskCount + " from " + A.getPegName() 
                    + " to " + C.getPegName());
        System.out.println("\t" + A.printStack(A.size()) + "\t\t\t" 
                    + B.printStack(B.size()) + "\t\t\t" + C.printStack(C.size()));
    }
    
    public static void sortTowers(int diskCount, Peg A, Peg B, Peg C){

        if (diskCount >= 1){
            sortTowers(diskCount - 1, A, C, B);
            C.push(A.pop());
            printTowers(diskCount, A, B, C);
            sortTowers(diskCount - 1, B, A, C);                   
         
        }
    } 
}
