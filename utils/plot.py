
import argparse
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def main(args):
    df  = pd.read_csv(args.log, sep=" ", header=0)
    df = df[['method', 'N', 'User(s)']]
    #print(df[df['method']=="sequential"]['N'])

    # plt.figure()

    # PLOT:
    fig, ax = plt.subplots()
    ax.scatter(x=df[df['method']=="sequential"]['N'], y=df[df['method']=="sequential"]['User(s)'], label="sequential")

    axes = plt.gca()
    y = np.polyfit(df[df['method']=="sequential"]['N'].values.flatten(), df[df['method']=="sequential"]['User(s)'].values.flatten(), deg=3)
    X_plot = np.linspace(axes.get_xlim()[0],axes.get_xlim()[1],100)
    y_plot = X_plot**3*y[0]+X_plot**2*y[1]+X_plot*y[2]+y[3]
    plt.plot(X_plot, y_plot, '-')

    # ax.legend()

    ax.scatter(x=df[df['method']=="my_eigen_matmult"]['N'], y=df[df['method']=="my_eigen_matmult"]['User(s)'], label="eigen_vectorization")
    y = np.polyfit(df[df['method']=="my_eigen_matmult"]['N'].values.flatten(), df[df['method']=="my_eigen_matmult"]['User(s)'].values.flatten(), deg=2)
    X_plot = np.linspace(axes.get_xlim()[0],axes.get_xlim()[1],100)
    #
    # axes = plt.gca()
    y_plot = X_plot**2*y[0]+X_plot*y[1]+y[2]
    plt.plot(X_plot, y_plot, '-')

    # ax.legend()

    ax.scatter(x=df[df['method']=="my_eigen_matmult_no_vect"]['N'], y=df[df['method']=="my_eigen_matmult_no_vect"]['User(s)'], label="eigen_no_vectorization")
    y = np.polyfit(df[df['method']=="my_eigen_matmult_no_vect"]['N'].values.flatten(), df[df['method']=="my_eigen_matmult_no_vect"]['User(s)'].values.flatten(), deg=2)
    X_plot = np.linspace(axes.get_xlim()[0],axes.get_xlim()[1],100)
    #
    # axes = plt.gca()
    y_plot = X_plot**2*y[0]+X_plot*y[1]+y[2]
    plt.plot(X_plot, y_plot, '-')



    ax.legend()
    ax.set_xlabel("N")
    ax.set_ylabel("t (s)")
    ax.set_title("time - N for each method")
    ax.grid()
    plt.savefig('times.png')
    # etc.

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument('-l', '--log', help='log',
                        type=str, default="log/comparison.log")

    args = parser.parse_args()
    main(args)
