package tec;

import java.lang.Class;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.Object;

class LancerTests {

    static private void lancer(Class c) throws Exception{
	Method[] methods = c.getMethods();
	int j = 0;
	
        for(int i = 0; i < methods.length; i++){
	    if (methods[i].getName().substring(0,4).equals("test")) {
		try {
		    Object o = c.newInstance();
		    Object[] parameters = null;
		    methods[i].invoke(o, parameters);
		} catch (InvocationTargetException e) {
		    e.getCause();
		}
		System.out.print(".");
		j++;
	    }
	}
    System.out.println("(" + j + "):OK: " + c.getName());
}

static public void main(String[] args) throws Exception{
        for(int i = 0; i < args.length; i++){
            Class c = Class.forName(args[i]);
            lancer(c);
        }
    }

}
