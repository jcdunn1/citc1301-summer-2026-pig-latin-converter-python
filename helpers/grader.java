import java.io.*;
import java.lang.reflect.*;
import java.nio.file.*;
import java.util.*;

public class grader {
    static {
        System.setIn(new EchoInputStream(System.in));
    }

    private static String pickMainClass(String[] args) throws IOException {
        if (args.length > 0)
            return args[0];

        String env = System.getenv("STUDENT_MAIN");
        if (env != null && !env.isBlank())
            return env;

        try (var files = Files.walk(Path.of("."))) {
            return files
                    .filter(p -> p.toString().endsWith(".class"))
                    .map(p -> p.getFileName()
                        .toString()
                        .replaceFirst("\\.class$", ""))
                    .filter(name -> !name.equals("grader") && !name.equals("EchoInputStream"))
                    .filter(grader::hasMain)
                    .findFirst()
                    .orElseThrow(() ->
                            new IllegalStateException(
                                "❌  No student main class with public static void main found.\n" +
                                "    Pass it on the CLI or set STUDENT_MAIN."));
        }
    }

    private static boolean hasMain(String className) {
        try {
            Method m = Class.forName(className).getMethod(
                    "main", String[].class);
            return Modifier.isStatic(m.getModifiers());
        } catch (ReflectiveOperationException e) {
            return false;
        }
    }

    public static void main(String[] args) throws Exception {
        String target = pickMainClass(args);

        Method main = Class.forName(target).getMethod(
                "main", String[].class);
        main.invoke(null, (Object) new String[0]);
    }
}

class EchoInputStream extends FilterInputStream {
    EchoInputStream(InputStream in) { super(in); }

    @Override public int read() throws IOException {
        int b = super.read();
        if (b != -1) System.out.write(b);
        return b;
    }
    @Override public int read(byte[] buf, int off, int len) throws IOException {
        int n = super.read(buf, off, len);
        if (n > 0) System.out.write(buf, off, n);
        return n;
    }
}
