#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define Row 9
#define Col 10

typedef pair<int , int> Pair;   // a cordinate point n x-y plane
typedef pair<double , pair<int ,int>> pPair;

struct cell{
    int parent_i,parent_j;   // will contain the value of parent cordinates
    double f,g,h;            // f = total distance, g = distance of present box with destination , h = huerstic
};

bool isValid(int row , int col){          // to check if a cordinate is valid or not
    return (row>=0) && (row<Row) && (col>=0) && (col<Col);
}

bool isUnblocked(int graph[][Col], int row, int col){   // to check if a box is unblocked or not
    if(graph[row][col] == 1)  return true;
    else return false;
}

bool isDestination(Pair dest, int row, int col){   // to check if a box is the destination
    if(dest.first == row && dest.second == col)
    return true;
    else
    return false;
}

double CalculateHValue(Pair dist, int row, int col){               // to calculate the value of heuristic
    return ((double) sqrt((row-dist.first)*(row-dist.first) + (col-dist.second)*(col-dist.second)));
}


void tracePath(cell cellDetails[][Col], Pair dest)
{
    printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push (make_pair (row, col));
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        cout<<"-> ("<<p.first<<","<<p.second<<")";
    }

    return;
}

void aStarSearch(int graph[][Col], Pair src, Pair dest){
    if(!isValid(src.first,src.second)) {  cout<<"Starting point is not valid"<<endl;  return;   }
    if(!isValid(dest.first,dest.second)) {   cout<<"Destination point is not valid"<<endl; return; }
    if(!isUnblocked(graph[][Col], src.first, src.second)) { cout<<"Starting point is blocked"<<endl;  return; }
    if(!isUnblocked(graph[][Col],dest.first,dest.second)) { cout<<"Destination point is blocked"<<endl;  return; }
    if(isDestination(dest,src.first,src.second)) {cout<<"Already at the destination"<<endl;  return ;}


    bool closedList[Row][Col];      // create a list to mark the boxes which have been reached
    memset(closedList, false, sizeof (closedList));  // putting false to all boxes initially as no box is reached

    cell CellDetails[Row][Col];  // this will store details of all the cells which is reached and will be used to get path

    int i, j;

    for (i=0; i<Row; i++)                       /* initially putting all distances as infinite and parent of
    {                                               all points are set to be (-1,-1) */
        for (j=0; j<Col; j++)
        {
            CellDetails[i][j].f = FLT_MAX;
            CellDetails[i][j].g = FLT_MAX;
            CellDetails[i][j].h = FLT_MAX;
            CellDetails[i][j].parent_i = -1;
            CellDetails[i][j].parent_j = -1;
        }


    i = src.first, j = src.second;
    CellDetails[i][j].f = 0.0;
    CellDetails[i][j].g = 0.0;
    CellDetails[i][j].h = 0.0;
    CellDetails[i][j].parent_i = i;
    CellDetails[i][j].parent_j = j;


    set<pPair> openList;
    openList.insert(make_pair (0.0, make_pair (i, j)));
    bool foundDest = false;

    while(!openList.empty()){

        pPair p = *openList.begin();

        openList.erase(openList.begin());       // Remove this vertex from the open list

        i = p.second.first;                           // Add this vertex to the closed list
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;          // variables to update values of  cell information

        if (isValid(i-1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i-1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i-1][j].parent_i = i;
                CellDetails[i-1][j].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i-1, j, dest);
                fNew = gNew + hNew;


                if (CellDetails[i-1][j].f == FLT_MAX || CellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i-1, j)));

                    // Update the details of this cell
                    CellDetails[i-1][j].f = fNew;
                    CellDetails[i-1][j].g = gNew;
                    CellDetails[i-1][j].h = hNew;
                    CellDetails[i-1][j].parent_i = i;
                    CellDetails[i-1][j].parent_j = j;
                }
            }

         }


        if (isValid(i+1, j) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i+1, j, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i+1][j].parent_i = i;
                CellDetails[i+1][j].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i-1, j, dest);
                fNew = gNew + hNew;


                if (CellDetails[i+1][j].f == FLT_MAX || CellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i+1, j)));

                    // Update the details of this cell
                    CellDetails[i+1][j].f = fNew;
                    CellDetails[i+1][j].g = gNew;
                    CellDetails[i+1][j].h = hNew;
                    CellDetails[i+1][j].parent_i = i;
                    CellDetails[i+1][j].parent_j = j;
                }
            }

         }


        if (isValid(i, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i][j+1].parent_i = i;
                CellDetails[i][j+1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i][j+1] == false && isUnBlocked(grid, i, j+1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i, j+1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i][j+1].f == FLT_MAX || CellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i, j+1)));

                    // Update the details of this cell
                    CellDetails[i][j+1].f = fNew;
                    CellDetails[i][j+1].g = gNew;
                    CellDetails[i][j+1].h = hNew;
                    CellDetails[i][j+1].parent_i = i;
                    CellDetails[i][j+1].parent_j = j;
                }
            }

         }




        if (isValid(i, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i][j-1].parent_i = i;
                CellDetails[i][j-1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i, j-1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i][j-1].f == FLT_MAX || CellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i, j-1)));

                    // Update the details of this cell
                    CellDetails[i][j-1].f = fNew;
                    CellDetails[i][j-1].g = gNew;
                    CellDetails[i][j-1].h = hNew;
                    CellDetails[i][j-1].parent_i = i;
                    CellDetails[i][j-1].parent_j = j;
                }
            }

         }



        if (isValid(i-1, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i-1, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i-1][j+1].parent_i = i;
                CellDetails[i-1][j+1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i-1][j+1] == false && isUnBlocked(grid, i-1, j+1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i-1, j+1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i-1][j+1].f == FLT_MAX || CellDetails[i-1][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i-1, j)));

                    // Update the details of this cell
                    CellDetails[i-1][j+1].f = fNew;
                    CellDetails[i-1][j+1].g = gNew;
                    CellDetails[i-1][j+1].h = hNew;
                    CellDetails[i-1][j+1].parent_i = i;
                    CellDetails[i-1][j+1].parent_j = j;
                }
            }

         }



        if (isValid(i-1, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i-1, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i-1][j-1].parent_i = i;
                CellDetails[i-1][j-1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i-1][j-1] == false && isUnBlocked(grid, i-1, j-1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i-1, j-1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i-1][j-1].f == FLT_MAX || CellDetails[i-1][j-1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i-1, j)));

                    // Update the details of this cell
                    CellDetails[i-1][j-1].f = fNew;
                    CellDetails[i-1][j-1].g = gNew;
                    CellDetails[i-1][j-1].h = hNew;
                    CellDetails[i-1][j-1].parent_i = i;
                    CellDetails[i-1][j-1].parent_j = j;
                }
            }

         }



        if (isValid(i+1, j+1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i+1, j+1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i+1][j+1].parent_i = i;
                CellDetails[i+1][j+1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i+1][j+1] == false && isUnBlocked(grid, i+1, j+1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i+1, j+1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i+1][j+1].f == FLT_MAX || CellDetails[i+1][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i+1, j)));

                    // Update the details of this cell
                    CellDetails[i+1][j+1].f = fNew;
                    CellDetails[i+1][j+1].g = gNew;
                    CellDetails[i+1][j+1].h = hNew;
                    CellDetails[i+1][j+1].parent_i = i;
                    CellDetails[i+1][j+1].parent_j = j;
                }
            }

         }


          if (isValid(i-1, j-1) == true)
        {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i+1, j-1, dest) == true)
            {
                // Set the Parent of the destination cell
                CellDetails[i+1][j-1].parent_i = i;
                CellDetails[i+1][j-1].parent_j = j;
                cout<<"The destination cell is found\n";
                tracePath (CellDetails, dest);
                foundDest = true;
                return;
            }

            else if (closedList[i+1][j-1] == false && isUnBlocked(grid, i+1, j-1) == true)
            {
                gNew = CellDetails[i][j].g + 1.0;
                hNew = CalculateHValue(i+1, j-1, dest);
                fNew = gNew + hNew;


                if (CellDetails[i+1][j-1].f == FLT_MAX || CellDetails[i+1][j-1].f > fNew)
                {
                    openList.insert( make_pair(fNew,make_pair(i+1, j)));

                    // Update the details of this cell
                    CellDetails[i+1][j-1].f = fNew;
                    CellDetails[i+1][j-1].g = gNew;
                    CellDetails[i+1][j-1].h = hNew;
                    CellDetails[i+1][j-1].parent_i = i;
                    CellDetails[i+1][j-1].parent_j = j;
                }
            }

         }

    if (foundDest == false)
    printf("Failed to find the Destination Cell\n");

    return;
}
}

int main()
{
     /* Description of the Grid-:
	1--> The cell is not blocked
	0--> The cell is blocked */
	int graph[ROW][COL] =
	{  // 1  2  3  4  5  6  7  8  9  10
	  	{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, //1
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, //2
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, //3
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, //4
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, //5
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, //6
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, //7
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, //8
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }  //9
	};

	// Source is the left-most bottom-most corner
	Pair src = make_pair(8, 0);

	// Destination is the left-most top-most corner
	Pair dest = make_pair(8, 2);

	aStarSearch(graph, src, dest);
    return 0;
}
