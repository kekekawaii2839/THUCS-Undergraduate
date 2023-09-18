import matplotlib.pyplot as plt
import os

def visualize_loss(train_loss_list, train_interval, val_loss_list, val_interval, dataset, out_dir):
    # Create x-axis values based on intervals
    train_x_values = [i * train_interval for i in range(len(train_loss_list))]
    val_x_values = [i * val_interval for i in range(len(val_loss_list))]
    
    # Plot training loss
    plt.plot(train_x_values, train_loss_list, label='Training Loss', color='blue')
    
    # Plot validation loss
    plt.plot(val_x_values, val_loss_list, label='Validation Loss', color='red')
    
    # Add labels and title
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.title('Loss Visualization for {}'.format(dataset))
    
    # Add legend
    plt.legend()
    
    # Save the plot to the specified output directory
    plt.savefig(os.path.join(out_dir, 'loss.png'))