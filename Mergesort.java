import java.util.Random;

public class Mergesort {

	private static double[] merge(double[] a, double[] b) {
		double[] c = new double[a.length + b.length];
		int i = 0, j = 0;
		for (int k = 0; k < c.length; k++) {
			if (i >= a.length) c[k] = b[j++];
			else if (j >= b.length) c[k] = a[i++];
			else if (a[i] <= b[j]) c[k] = a[i++];
			else c[k] = b[j++];
		}
		return c;
	}

	public static double[] mergesort(double[] input) {
		int N = input.length;
		if (N <= 1) return input;
		double[] a = new double[N/2];
		double[] b = new double[N - N/2];

		for (int i = 0; i < a.length; i++)
			a[i] = input[i];
		for (int i = 0; i < b.length; i++)
			b[i] = input[i + a.length];
		return merge(mergesort(a), mergesort(b));
	}

	private static boolean isSorted(double[] a) {
		for (int i = 1; i < a.length; i++) {
			if (a[i] < a[i-1]) return false;
		}
		return true;
	}

	public static void main(String[] args) {
		int N = Integer.parseInt(args[0]);
		double[] a = new double[N];

		Random rand = new Random();

		for (int i = 0; i < N; i++)
			a[i] = rand.nextDouble();
		a = mergesort(a);
		for (int i = 0; i < N; i++) {
			System.out.println(a[i] + " ");
		}
		System.out.println();
		System.out.println(isSorted(a));
	}
}