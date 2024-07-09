import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DN11 {
    public static void main(String[] args) {
        JFrame okno = new JFrame("VELIKE ČRKE");
        okno.setSize(1000, 500);
        okno.setLayout(new GridLayout(1, 3));


        JTextArea besedilo = new JTextArea();

        JButton gumb= new JButton("--> pretvori");

        JTextArea prazenText = new JTextArea();
        prazenText.setEditable(false);

        gumb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String text = besedilo.getText();
                prazenText.setText(text.toUpperCase());
            }
        });

        okno.add(besedilo);
        okno.add(gumb);
        okno.add(prazenText);

        okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        okno.setVisible(true);
    }
}