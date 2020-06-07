using System;
using UnityEngine;

public class ProgressControl : MonoBehaviour {
    private Transform progressBar = null;
    private Vector3 startPoint = Vector3.zero;
    private Vector3 endPoint = Vector3.zero;
    private Vector3 movePoint;

    public bool IsFilled {
        get {
            return Vector3.Distance(progressBar.position, endPoint) <= 0f;
        }
    }

    private void Start() {
        progressBar = transform.Find("Progress Bar");
        if (progressBar == null) throw new Exception("Progress bar not found");
        var startPointObj = transform.Find("Start Point");
        if (startPointObj == null) throw new Exception("Start point not found");
        var endPointObj = transform.Find("End Point");
        if (endPointObj == null) throw new Exception("End point not found");

        startPoint = startPointObj.position;
        endPoint = endPointObj.position;
        movePoint = progressBar.position;
    }

    private void Update() {
        progressBar.position = Vector3.MoveTowards(progressBar.position, movePoint, 0.1f);
       
    }

    public void fillProgress(float amount) {
        float distance = (startPoint - endPoint).magnitude;
        float unit = distance * Mathf.Clamp(amount, 0.0f, 1.0f);
        movePoint = startPoint + new Vector3(unit, 0, 0);
    }
}
