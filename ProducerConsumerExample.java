import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

// Class representing the bounded buffer
class BoundedBuffer {
    private final int capacity;
    private final Queue<Integer> queue;

    public BoundedBuffer(int capacity) {
        this.capacity = capacity;
        this.queue = new LinkedList<>();
    }

    // Method to produce an item
    public synchronized void produce(int value) throws InterruptedException {
        while (queue.size() == capacity) {
            System.out.println("Buffer is full. Producer is waiting...");
            wait();
        }
        queue.add(value);
        System.out.println("Produced: " + value);
        notifyAll();
    }

    // Method to consume an item
    public synchronized int consume() throws InterruptedException {
        while (queue.isEmpty()) {
            System.out.println("Buffer is empty. Consumer is waiting...");
            wait();
        }
        int value = queue.poll();
        System.out.println("Consumed: " + value);
        notifyAll();
        return value;
    }
}

// Class representing a producer
class Producer implements Runnable {
    private final BoundedBuffer buffer;
    private final int itemsToProduce;

    public Producer(BoundedBuffer buffer, int itemsToProduce) {
        this.buffer = buffer;
        this.itemsToProduce = itemsToProduce;
    }

    @Override
    public void run() {
        try {
            for (int value = 0; value < itemsToProduce; value++) {
                buffer.produce(value);
                Thread.sleep((int) (Math.random() * 1000)); // Simulate work
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Class representing a consumer
class Consumer implements Runnable {
    private final BoundedBuffer buffer;
    private final int itemsToConsume;

    public Consumer(BoundedBuffer buffer, int itemsToConsume) {
        this.buffer = buffer;
        this.itemsToConsume = itemsToConsume;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < itemsToConsume; i++) {
                buffer.consume();
                Thread.sleep((int) (Math.random() * 1000)); // Simulate work
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Main class to run the producer-consumer example
public class ProducerConsumerExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get buffer capacity
        System.out.print("Enter buffer capacity: ");
        int bufferCapacity = scanner.nextInt();
        BoundedBuffer buffer = new BoundedBuffer(bufferCapacity);

        while (true) {
            // Display menu
            System.out.println("\nMenu:");
            System.out.println("1. Produce or Consume");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter 1 for Producer or 2 for Consumer: ");
                    int subChoice = scanner.nextInt();
                    if (subChoice == 1) {
                        // Producer operation
                        System.out.print("Enter number of items to produce: ");
                        int itemsToProduce = scanner.nextInt();
                        Thread producer = new Thread(new Producer(buffer, itemsToProduce));
                        producer.start();
                        try {
                            producer.join();
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    } else if (subChoice == 2) {
                        // Consumer operation
                        System.out.print("Enter number of items to consume: ");
                        int itemsToConsume = scanner.nextInt();
                        Thread consumer = new Thread(new Consumer(buffer, itemsToConsume));
                        consumer.start();
                        try {
                            consumer.join();
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    } else {
                        System.out.println("Invalid choice. Please enter 1 for Producer or 2 for Consumer.");
                    }
                    break;

                case 3:
                    // Exit operation
                    System.out.println("Exiting...");
                    scanner.close();
                    System.exit(0);
                    break;

                default:
                    System.out.println("Invalid choice. Please enter 1 or 3.");
                    break;
            }
        }
    }
}
