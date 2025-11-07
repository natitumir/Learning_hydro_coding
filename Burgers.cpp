#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

//minmod slope limiter for reconstruction
inline double minmod(double alpha,double beta)
{
    if(abs(alpha)<abs(beta) && alpha*beta>0)
    {
        return alpha;
    }
    else if(abs(alpha)>abs(beta) && alpha*beta>0)
    {
        return beta;
    }
    else return 0;
}



//In the integrator, I will use a time loop, which will update time steps. Inside the time loop, I will definitely need space
//loop to work with the values of the variables.
void integrator(double ti, double tf, double xi, double xf, double dx, vector<double> q, int num_space_div) {
    double dt=0.01;
    double x=xi+dx/2.0;
    ofstream burgers("burgers.txt");
    for(int i=2; i<=num_space_div+1 ; i++){
        burgers<<ti<<" "<<x<<" "<<q[i]<<endl;
        x=x+dx;
    }
    
    vector<double> numeric_Flux(num_space_div+1,0.0);
    vector<double> q_reconstructed_L(num_space_div+1,0.0);
    vector<double> q_reconstructed_R(num_space_div+1,0.0);

    double t=ti;

    while(t<=tf){

        for(int j=0; j<=num_space_div;j++){
            q_reconstructed_L[j]= q[j+1]+ (dx/2.0)*minmod((q[j+2]-q[j+1])/dx,(q[j+1]-q[j])/dx);
            q_reconstructed_R[j]= q[j+2]- (dx/2.0)*minmod((q[j+3]-q[j+2])/dx,(q[j+2]-q[j+1])/dx);
        }
        for(int j=0; j<=num_space_div; j++){
            numeric_Flux[j]= 0.5*(0.5*(q_reconstructed_L[j]*q_reconstructed_L[j]+q_reconstructed_R[j]*q_reconstructed_R[j])-0.5*(q_reconstructed_L[j]+q_reconstructed_R[j])*(q_reconstructed_R[j]-q_reconstructed_L[j]));
        }
        

        vector<double> q_hold = q;
        for(int i=2; i<=num_space_div+1;i++){
            q[i]= q[i] + (dt/2.0)*((numeric_Flux[i-2]-numeric_Flux[i-1])/dx); 
        }
        q[0]=q[2];
        q[1]=q[3];
        q[num_space_div+2]=q[num_space_div];
        q[num_space_div+3]=q[num_space_div+1];

        for(int j=0; j<=num_space_div;j++){
            q_reconstructed_L[j]= q[j+1]+ (dx/2.0)*minmod((q[j+2]-q[j+1])/dx,(q[j+1]-q[j])/dx);
            q_reconstructed_R[j]= q[j+2]- (dx/2.0)*minmod((q[j+3]-q[j+2])/dx,(q[j+2]-q[j+1])/dx);
        }
        for(int j=0; j<=num_space_div; j++){
            numeric_Flux[j]= 0.5*(0.5*(q_reconstructed_L[j]*q_reconstructed_L[j]+q_reconstructed_R[j]*q_reconstructed_R[j])-0.5*(q_reconstructed_L[j]+q_reconstructed_R[j])*(q_reconstructed_R[j]-q_reconstructed_L[j]));
        }

        for(int i=2; i<=num_space_div+1;i++){
            q[i]= q_hold[i] + (dt)*((numeric_Flux[i-2]-numeric_Flux[i-1])/dx); 
        }
        q[0]=q[2];
        q[1]=q[3];
        q[num_space_div+2]=q[num_space_div];
        q[num_space_div+3]=q[num_space_div+1];

        t=t+dt;
        double x=xi+dx/2.0;
        for(int i=2; i<=num_space_div+1 ; i++){
            burgers<<t<<" "<<x<<" "<<q[i]<<endl;
            x=x+dx;
        }
    }



    
}


int main() {
    double xi = -10;
    double xf= 10;
    int num_space_div= 200;
    double dx= (xf-xi)/(double)num_space_div ;
    double ti = 0;
    double tf = 5;
    

    vector<double> q(num_space_div+4,0.0);
    for(int i=0; i<(num_space_div+4)/2;i++){
        q[i]=2.2;
    }
    for(int i=(num_space_div+4)/2; i<num_space_div+4;i++){
        q[i]=1.1;
    }

    integrator(ti,tf,xi,xf,dx,q,num_space_div);

    



    return 0;
}